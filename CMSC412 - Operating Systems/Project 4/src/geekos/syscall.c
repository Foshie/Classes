/*
 * System call handlers
 * Copyright (c) 2003, Jeffrey K. Hollingsworth <hollings@cs.umd.edu>
 * Copyright (c) 2003,2004 David Hovemeyer <daveho@cs.umd.edu>
 * $Revision: 1.65 $
 *
 * This is free software.  You are permitted to use,
 * redistribute, and modify it as specified in the file "COPYING".
 */

#include <geekos/syscall.h>
#include <geekos/errno.h>
#include <geekos/kthread.h>
#include <geekos/int.h>
#include <geekos/elf.h>
#include <geekos/malloc.h>
#include <geekos/screen.h>
#include <geekos/keyboard.h>
#include <geekos/string.h>
#include <geekos/user.h>
#include <geekos/timer.h>
#include <geekos/vfs.h>
#include <geekos/signal.h>
#include <geekos/sem.h>

#include <geekos/sys_net.h>
#include <geekos/projects.h>

/*
 * Allocate a buffer for a user string, and
 * copy it into kernel space.
 * Interrupts must be disabled.
 */
/* "extern" to note that it's used by semaphore and networking system calls, defined 
   in another file */
extern int Copy_User_String(ulong_t uaddr, ulong_t len, ulong_t maxLen,
                            char **pStr) {
    int rc = 0;
    char *str;

    /* Ensure that string isn't too long. */
    if (len > maxLen)
        return EINVALID;

    /* Allocate space for the string. */
    str = (char *)Malloc(len + 1);
    if (str == 0) {
        rc = ENOMEM;
        goto done;
    }

    /* Copy data from user space. */
    if (!Copy_From_User(str, uaddr, len)) {
        rc = EINVALID;
        Free(str);
        goto done;
    }
    str[len] = '\0';

    /* Success! */
    *pStr = str;

  done:
    return rc;
}

/*
 * Null system call.
 * Does nothing except immediately return control back
 * to the interrupted user program.
 * Params:
 *  state - processor registers from user mode
 *
 * Returns:
 *   always returns the value 0 (zero)
 */
static int Sys_Null(struct Interrupt_State *state) {
    return 0;
}

/*
 * Limit system call.
 */
static int Sys_Limit(struct Interrupt_State *state) {
    TODO_P(PROJECT_LIMIT_SYSCALLS_SYSCALL, "Need to Implement Sys_Limit");
}

/*
 * Exit system call.
 * The interrupted user process is terminated.
 * Params:
 *   state->ebx - process exit code
 * Returns:
 *   Never returns to user mode!
 */
static int Sys_Exit(struct Interrupt_State *state) {
    Exit(state->ebx);
    /* We will never get here. */
}

/*
** Shutdown Computer
** Normaly not within a user's powers,
** but it helps automate testing
*/
extern void shutMeDown();       /* is in keyboard.c for odd reasons */
static int Sys_ShutDown(struct Interrupt_State *state) {
    Print("------------------- THE END ------------------\n");
    shutMeDown();
    /* We will never get here. */
    return 0;
}

/*
 * Print a string to the console.
 * Params:
 *   state->ebx - user pointer of string to be printed
 *   state->ecx - number of characters to print
 * Returns: 0 if successful, -1 if not
 */
static int Sys_PrintString(struct Interrupt_State *state) {
    int rc = 0;
    uint_t length = state->ecx;
    char *buf = 0;

    if (length > 0) {
        /* Copy string into kernel. */
        if ((rc =
             Copy_User_String(state->ebx, length, 1023, (char **)&buf)) != 0)
            goto done;

        /* Write to console. */
        Put_Buf(buf, length);
    }

  done:
    if (buf != 0)
        Free(buf);
    return rc;
}

/*
 * Get a single key press from the console.
 * Suspends the user process until a key press is available.
 * Params:
 *   state - processor registers from user mode
 * Returns: the key code
 *          -1 if this is a background process
 */
static int Sys_GetKey(struct Interrupt_State *state) {
    return Wait_For_Key();
}

/*
 * Set the current text attributes.
 * Params:
 *   state->ebx - character attributes to use
 * Returns: always returns 0
 */
static int Sys_SetAttr(struct Interrupt_State *state) {
    Set_Current_Attr((uchar_t) state->ebx);
    return 0;
}

/*
 * Get the current cursor position.
 * Params:
 *   state->ebx - pointer to user int where row value should be stored
 *   state->ecx - pointer to user int where column value should be stored
 * Returns: 0 if successful, -1 otherwise
 */
static int Sys_GetCursor(struct Interrupt_State *state) {
    int row, col;
    Get_Cursor(&row, &col);
    if (!Copy_To_User(state->ebx, &row, sizeof(int)) ||
        !Copy_To_User(state->ecx, &col, sizeof(int)))
        return -1;
    return 0;
}

/*
 * Set the current cursor position.
 * Params:
 *   state->ebx - new row value
 *   state->ecx - new column value
 * Returns: 0 if successful, -1 otherwise
 */
static int Sys_PutCursor(struct Interrupt_State *state) {
    return Put_Cursor(state->ebx, state->ecx) ? 0 : -1;
}

/*
 * Create a new user process.
 * Params:
 *   state->ebx - user address of name of executable
 *   state->ecx - length of executable name
 *   state->edx - user address of command string
 *   state->esi - length of command string
 *   state->edi == whether to spawn in the background
 * Returns: pid of process if successful, error code (< 0) otherwise
 */
static int Sys_Spawn(struct Interrupt_State *state) {
    int rc;
    char *program = 0;
    char *command = 0;
    struct Kernel_Thread *process;

    /* Copy program name and command from user space. */
    if ((rc =
         Copy_User_String(state->ebx, state->ecx, VFS_MAX_PATH_LEN,
                          &program)) != 0 ||
        (rc = Copy_User_String(state->edx, state->esi, 1023, &command)) != 0)
        goto done;

    Enable_Interrupts();


    /*
     * Now that we have collected the program name and command string
     * from user space, we can try to actually spawn the process.
     */
    rc = Spawn(program, command, &process);
    if (rc == 0) {
        KASSERT(process != 0);
        rc = process->pid;
    }

    Disable_Interrupts();

  done:
    if (program != 0)
        Free(program);
    if (command != 0)
        Free(command);

    return rc;
}

/*
 * Wait for a process to exit.
 * Params:
 *   state->ebx - pid of process to wait for
 * Returns: the exit code of the process,
 *   or error code (< 0) on error
 */
static int Sys_Wait(struct Interrupt_State *state) {
    int exitCode;
    struct Kernel_Thread *kthread = Lookup_Thread(state->ebx, 0);
    if (kthread == 0)
        return -12;

    Enable_Interrupts();
    exitCode = Join(kthread);
    Disable_Interrupts();

    return exitCode;
}

/*
 * Get pid (process id) of current thread.
 * Params:
 *   state - processor registers from user mode
 * Returns: the pid of the current thread
 */
static int Sys_GetPID(struct Interrupt_State *state) {
    return g_currentThread->pid;
}


/*
 * Get information about the running processes
 * Params:
 *   state->ebx - pointer to user memory containing an array of
 *   Process_Info structs
 *   state->ecx - length of the passed in array in memory
 * Returns: -1 on failure
 *          0 if size of user memory too small
 *          N the number of entries in the table, on success
 */
static int Sys_PS(struct Interrupt_State *state) {
  TODO_P(PROJECT_BACKGROUND_JOBS, "Sys_PS system call");
}


/*
 * Send a signal to a process
 * Params:
 *   state->ebx - pid of process to send signal to
 *   state->ecx - signal number
 * Returns: 0 on success or error code (< 0) on error
 */
static int Sys_Kill(struct Interrupt_State *state) {
  TODO_P(PROJECT_BACKGROUND_JOBS, "Sys_Kill system call");
}

/*
 * Register a signal handler for a process
 * Params:
 *   state->ebx - pointer to handler function
 *   state->ecx - signal number
 * Returns: 0 on success or error code (< 0) on error
 */
static int Sys_Signal(struct Interrupt_State *state) {
    TODO_P(PROJECT_SIGNALS, "Sys_Signal system call");
}

/*
 * Register the Return_Signal trampoline for this process.
 * Signals cannot be delivered until this is registered.
 * Params:
 *   state->ebx - pointer to Return_Signal function
 *   state->ecx - pointer to the default handler
 *   state->edx - pointer to the ignore handler
 *
 * Returns: 0 on success or error code (< 0) on error
 */
static int Sys_RegDeliver(struct Interrupt_State *state) {
    // TODO("Sys_RegDeliver system call");
    TODO_P(PROJECT_SIGNALS, "Sys_RegDeliver system call");
    return 0;
}

/*
 * Complete signal handling for this process.
 * Params:
 *   none
 *
 * Returns: 0 on success or error code (< 0) on error
 */
static int Sys_ReturnSignal(struct Interrupt_State *state) {
    TODO_P(PROJECT_SIGNALS, "Sys_ReturnSignal system call");
}

/*
 * Reap a child process that has died
 * Params:
 *   state->ebx - pointer to status of process reaped
 * Returns: pid of reaped process on success, -1 on error.
 */
static int Sys_WaitNoPID(struct Interrupt_State *state) {
  TODO_P(PROJECT_SIGNALS, "Sys_WaitNoPID system call");
}

/*
 * Set the scheduling policy.
 * Params:
 *   state->ebx - policy,
 *   state->ecx - number of ticks in quantum
 * Returns: 0 if successful, -1 otherwise
 */
static int Sys_SetSchedulingPolicy(struct Interrupt_State *state) {
  TODO_P(PROJECT_SCHEDULING, "SetSchedulingPolicy system call");
}

/*
 * Get the time of day.
 * Params:
 *   state - processor registers from user mode
 *
 * Returns: value of the g_numTicks global variable
 */
static int Sys_GetTimeOfDay(struct Interrupt_State *state) {
  TODO_P(PROJECT_SCHEDULING, "GetTimeOfDay system call");
}

/*
 * Mount a filesystem.
 * Params:
 * state->ebx - contains a pointer to the Mount_Syscall_Args structure
 *   which contains the block device name, mount prefix,
 *   and filesystem type
 *
 * Returns:
 *   0 if successful, error code if unsuccessful
 */
static int Sys_Mount(struct Interrupt_State *state) {
    int rc = 0;
    struct VFS_Mount_Request *args = 0;

    /* Allocate space for VFS_Mount_Request struct. */
    if ((args =
         (struct VFS_Mount_Request *)Malloc(sizeof(struct VFS_Mount_Request)))
        == 0) {
        rc = ENOMEM;
        goto done;
    }

    /* Copy the mount arguments structure from user space. */
    if (!Copy_From_User(args, state->ebx, sizeof(struct VFS_Mount_Request))) {
        rc = EINVALID;
        goto done;
    }

    /*
     * Hint: use devname, prefix, and fstype from the args structure
     * and invoke the Mount() VFS function.  You will need to check
     * to make sure they are correctly nul-terminated.
     */
    TODO("Mount system call");

  done:
    if (args != 0)
        Free(args);
    return rc;
}

/*
 * Open a file.
 * Params:
 *   state->ebx - address of user string containing path of file to open
 *   state->ecx - length of path
 *   state->edx - file mode flags
 *
 * Returns: a file descriptor (>= 0) if successful,
 *   or an error code (< 0) if unsuccessful
 */
static int Sys_Open(struct Interrupt_State *state) {
    TODO("Open system call");
}

/*
 * Open a directory.
 * Params:
 *   state->ebx - address of user string containing path of directory to open
 *   state->ecx - length of path
 *
 * Returns: a file descriptor (>= 0) if successful,
 *   or an error code (< 0) if unsuccessful
 */
static int Sys_OpenDirectory(struct Interrupt_State *state) {
    TODO("Open directory system call");
}

/*
 * Close an open file or directory.
 * Params:
 *   state->ebx - file descriptor of the open file or directory
 * Returns: 0 if successful, or an error code (< 0) if unsuccessful
 */
static int Sys_Close(struct Interrupt_State *state) {
    TODO("Close system call");
}

/*
 * Delete a file.
 * Params:
 *   state->ebx - address of user string containing path to delete
 *   state->ecx - length of path
 *
 * Returns: 0 if successful, error code (< 0) if unsuccessful
 */
static int Sys_Delete(struct Interrupt_State *state) {
    TODO("Delete system call");
}

/*
 * Read from an open file.
 * Params:
 *   state->ebx - file descriptor to read from
 *   state->ecx - user address of buffer to read into
 *   state->edx - number of bytes to read
 *
 * Returns: number of bytes read, 0 if end of file,
 *   or error code (< 0) on error
 */
static int Sys_Read(struct Interrupt_State *state) {
    TODO("Read system call");
}

/*
 * Read a directory entry from an open directory handle.
 * Params:
 *   state->ebx - file descriptor of the directory
 *   state->ecx - user address of struct VFS_Dir_Entry to copy entry into
 * Returns: 0 if successful, error code (< 0) if unsuccessful
 */
static int Sys_ReadEntry(struct Interrupt_State *state) {
    TODO("ReadEntry system call");
}

/*
 * Write to an open file.
 * Params:
 *   state->ebx - file descriptor to write to
 *   state->ecx - user address of buffer get data to write from
 *   state->edx - number of bytes to write
 *
 * Returns: number of bytes written,
 *   or error code (< 0) on error
 */
static int Sys_Write(struct Interrupt_State *state) {
    TODO("Write system call");
}

/*
 * Get file metadata.
 * Params:
 *   state->ebx - address of user string containing path of file
 *   state->ecx - length of path
 *   state->edx - user address of struct VFS_File_Stat object to store metadata in
 *
 * Returns: 0 if successful, error code (< 0) if unsuccessful
 */
static int Sys_Stat(struct Interrupt_State *state) {
    TODO("Stat system call");
}

/*
 * Get metadata of an open file.
 * Params:
 *   state->ebx - file descriptor to get metadata for
 *   state->ecx - user address of struct VFS_File_Stat object to store metadata in
 *
 * Returns: 0 if successful, error code (< 0) if unsuccessful
 */
static int Sys_FStat(struct Interrupt_State *state) {
    TODO("FStat system call");
}

/*
 * Change the access position in a file
 * Params:
 *   state->ebx - file descriptor
 *   state->ecx - position in file
 *
 * Returns: 0 if successful, error code (< 0) if unsuccessful
 */
static int Sys_Seek(struct Interrupt_State *state) {
    TODO("Seek system call");
}

/*
 * Create directory
 * Params:
 *   state->ebx - address of user string containing path of new directory
 *   state->ecx - length of path
 *
 * Returns: 0 if successful, error code (< 0) if unsuccessful
 */
static int Sys_CreateDir(struct Interrupt_State *state) {
    TODO("CreateDir system call");
}

/*
 * Flush filesystem buffers
 * Params: none
 * Returns: 0 if successful, error code (< 0) if unsuccessful
 */
static int Sys_Sync(struct Interrupt_State *state) {
    TODO("Sync system call");
}

/*
 * Format a device
 * Params:
 *   state->ebx - address of user string containing device to format
 *   state->ecx - length of device name string
 *   state->edx - address of user string containing filesystem type 
 *   state->esi - length of filesystem type string

 * Returns: 0 if successful, error code (< 0) if unsuccessful
 */
static int Sys_Format(struct Interrupt_State *state) {
    int rc = 0;
    char *devname = 0, *fstype = 0;

    if ((rc =
         Copy_User_String(state->ebx, state->ecx, BLOCKDEV_MAX_NAME_LEN,
                          &devname)) != 0 ||
        (rc =
         Copy_User_String(state->edx, state->esi, VFS_MAX_FS_NAME_LEN,
                          &fstype)) != 0)
        goto done;

    Enable_Interrupts();
    rc = Format(devname, fstype);
    Disable_Interrupts();

  done:
    if (devname != 0)
        Free(devname);
    if (fstype != 0)
        Free(fstype);
    return rc;
}

/*
 * Read a block from a device
 * Params:
 *   state->ebx - address of user string containing block device name
 *   state->ecx - length of block device name string
 *   state->edx - address of user buffer to read into
 *   state->esi - length to read into user buffer
 *   state->edi - block # to read from

 * Returns: 0 if successful, error code (< 0) if unsuccessful
 */
static int Sys_ReadBlock(struct Interrupt_State *state) {
    TODO("ReadBlock system call");
}

/*
 * Write a block to a device
 * Params:
 *   state->ebx - address of user string containing device name
 *   state->ecx - length of block device name string
 *   state->edx - address of user buffer to write
 *   state->esi - length to write to block
 *   state->edi - block # to write to

 * Returns: 0 if successful, error code (< 0) if unsuccessful
 */
static int Sys_WriteBlock(struct Interrupt_State *state) {
    TODO("WriteBlock system call");
}

/*
 * Global table of system call handler functions.
 */
const Syscall g_syscallTable[] = {
    Sys_Null,
    Sys_Exit,
    Sys_PrintString,
    Sys_GetKey,
    Sys_SetAttr,
    Sys_GetCursor,
    Sys_PutCursor,
    Sys_Spawn,
    Sys_Wait,
    Sys_GetPID,
    Sys_Kill,
    Sys_PS,
    Sys_Signal,
    Sys_RegDeliver,
    Sys_ReturnSignal, /* must be #14 */
    Sys_WaitNoPID,
    /* Scheduling and semaphore system calls. */
    Sys_SetSchedulingPolicy,
    Sys_GetTimeOfDay,
    Sys_Open_Semaphore,
    Sys_P,
    Sys_V,
    Sys_Close_Semaphore,
    /* File I/O system calls. */
    Sys_Mount,
    Sys_Open,
    Sys_OpenDirectory,
    Sys_Close,
    Sys_Delete,
    Sys_Read,
    Sys_ReadEntry,
    Sys_Write,
    Sys_Stat,
    Sys_FStat,
    Sys_Seek,
    Sys_CreateDir,
    Sys_Sync,
    Sys_Format,
    Sys_ShutDown,
    Sys_ReadBlock,
    Sys_WriteBlock,
    /* Networking calls */
    Sys_EthPacketSend,
    Sys_EthPacketReceive,
    Sys_Arp,
    Sys_RouteAdd,
    Sys_RouteDel,
    Sys_RouteGet,
    Sys_IPConfigure,
    Sys_IPGet,
    Sys_IPSend,
    /* Socket API */
    Sys_Socket,
    Sys_Bind,
    Sys_Listen,
    Sys_Accept,
    Sys_Connect,
    Sys_Send,
    Sys_Receive,
    Sys_SendTo,
    Sys_ReceiveFrom,
    Sys_CloseSocket,
    Sys_Limit
};

/*
 * Number of system calls implemented.
 */
const unsigned int g_numSyscalls = sizeof(g_syscallTable) / sizeof(Syscall);
