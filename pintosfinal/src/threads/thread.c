#include "threads/thread.h"
#include <debug.h>
#include <stddef.h>
#include <random.h>
#include <stdio.h>
#include <string.h>
#include "threads/flags.h"
#include "threads/interrupt.h"
#include "threads/intr-stubs.h"
#include "threads/palloc.h"
#include "threads/switch.h"
#include "threads/synch.h"
#include "threads/vaddr.h"
#ifdef USERPROG
#include "userprog/process.h"
#endif
#include "vm/memoryMap.h"
#include "vm/page.h"
//void file_close (struct file *);
/* Random value for struct thread's `magic' member.
   Used to detect stack overflow.  See the big comment at the top
   of thread.h for details. */
#define THREAD_MAGIC 0xcd6abf4b

/* List of processes in THREAD_READY state, that is, processes
   that are ready to run but not actually running. */


/* Idle thread. */
static struct thread *idle_thread;

/* Initial thread, the thread running init.c:main(). */
static struct thread *initial_thread;

/* Lock used by allocate_tid(). */
static struct lock tid_lock;

/* Stack frame for kernel_thread(). */
struct kernel_thread_frame 
  {
    void *eip;                  /* Return address. */
    thread_func *function;      /* Function to call. */
    void *aux;                  /* Auxiliary data for function. */
  };

/* Statistics. */
static long long idle_ticks;    /* # of timer ticks spent idle. */
static long long kernel_ticks;  /* # of timer ticks in kernel threads. */
static long long user_ticks;    /* # of timer ticks in user programs. */

/* Scheduling. */
#define TIME_SLICE 4            /* # of timer ticks to give each thread. */
static unsigned thread_ticks;   /* # of timer ticks since last yield. */

/* If false (default), use round-robin scheduler.
   If true, use multi-level feedback queue scheduler.
   Controlled by kernel command-line option "-o mlfqs". */
bool thread_mlfqs;

static void kernel_thread (thread_func *, void *aux);

static void idle (void *aux UNUSED);
static struct thread *running_thread (void);
static struct thread *next_thread_to_run (void);
static void init_thread (struct thread *, const char *name, int priority);
static bool is_thread (struct thread *) UNUSED;
static void *alloc_frame (struct thread *, size_t size);
static void schedule (void);
void schedule_tail (struct thread *prev);
static tid_t allocate_tid (void);
static struct list tid_thread_list;
struct thread *getThreadFromTid(struct list *tid_thread_list, int child_tid);
/* Initializes the threading system by transforming the code
   that's currently running into a thread.  This can't work in
   general and it is possible in this case only because loader.S
   was careful to put the bottom of the stack at a page boundary.

   Also initializes the run queue and the tid lock.

   After calling this function, be sure to initialize the page
   allocator before trying to create any threads with
   thread_create().

   It is not safe to call thread_current() until this function
   finishes. */
void
thread_init (void) 
{
  ASSERT (intr_get_level () == INTR_OFF);
  lock_init (&tid_lock);
  list_init (&ready_list);
  /* Set up a thread structure for the running thread. */
  initial_thread = running_thread ();
  init_thread (initial_thread, "main", PRI_DEFAULT);
  initial_thread->status = THREAD_RUNNING;
  initial_thread->tid = allocate_tid ();
  list_init(&(initial_thread->child_list));
  list_init(&(initial_thread->descriptor_table));
  initial_thread->availableDescriptor = 2;
  sema_init(&initial_thread->parentChildSemaphore, 0);
  sema_init(&initial_thread->childwaitSemaphore, 0);
  initial_thread->pThread = NULL;
  initial_thread->currentDirectory_sector =  ROOT_DIR_SECTOR ;   
  //hash_init(&(initial_thread->memoryMapTable),MemoryMapTable_Hash_Func, MemoryMapTable_Less, NULL);	
}

/* Starts preemptive thread scheduling by enabling interrupts.
   Also creates the idle thread. */
void
thread_start (void) 
{
  /* Create the idle thread. */
  struct semaphore idle_started;
  sema_init (&idle_started, 0);
  thread_create ("idle", PRI_MIN, idle, &idle_started);

  /* Start preemptive thread scheduling. */
  intr_enable ();

  /* Wait for the idle thread to initialize idle_thread. */
  sema_down (&idle_started);
}

/* Called by the timer interrupt handler at each timer tick.
   Thus, this function runs in an external interrupt context. */
void
thread_tick (void) 
{
  struct thread *t = thread_current ();

  /* Update statistics. */
  if (t == idle_thread)
    idle_ticks++;
#ifdef USERPROG
  else if (t->pagedir != NULL)
    user_ticks++;
#endif
  else
    kernel_ticks++;

  /* Enforce preemption. */
  if (++thread_ticks >= TIME_SLICE)
    intr_yield_on_return ();
}

/* Prints thread statistics. */
void
thread_print_stats (void) 
{
  printf ("Thread: %lld idle ticks, %lld kernel ticks, %lld user ticks\n",
          idle_ticks, kernel_ticks, user_ticks);
}

/* Creates a new kernel thread named NAME with the given initial
   PRIORITY, which executes FUNCTION passing AUX as the argument,
   and adds it to the ready queue.  Returns the thread identifier
   for the new thread, or TID_ERROR if creation fails.

   If thread_start() has been called, then the new thread may be
   scheduled before thread_create() returns.  It could even exit
   before thread_create() returns.  Contrariwise, the original
   thread may run for any amount of time before the new thread is
   scheduled.  Use a semaphore or some other form of
   synchronization if you need to ensure ordering.

   The code provided sets the new thread's `priority' member to
   PRIORITY, but no actual priority scheduling is implemented.
   Priority scheduling is the goal of Problem 1-3. */
tid_t
thread_create (const char *name, int priority,
               thread_func *function, void *aux) 
{
 //we need to check whether a thread can be created or not.

  struct thread *t;
  struct kernel_thread_frame *kf;
  struct switch_entry_frame *ef;
  struct switch_threads_frame *sf;
  tid_t tid;

  ASSERT (function != NULL);

  /* Allocate thread. */
  t = palloc_get_page (PAL_ZERO);
  if (t == NULL)
    return TID_ERROR;
 	//printf("%p\n",t);
  /* Initialize thread. */
  init_thread (t, name, priority);

  tid = t->tid = allocate_tid ();
 // printf("tid created %d\n",tid);
  /* Stack frame for kernel_thread(). */
  kf = alloc_frame (t, sizeof *kf);
  
  kf->eip = NULL;
  kf->function = function;
  kf->aux = aux;

  /* Stack frame for switch_entry(). */
  ef = alloc_frame (t, sizeof *ef);
  ef->eip = (void (*) (void)) kernel_thread;

  /* Stack frame for switch_threads(). */
  sf = alloc_frame (t, sizeof *sf);
  sf->eip = switch_entry;

/**/
  t->availableDescriptor = 2;
  list_init(&(t->descriptor_table));
  list_init(&(t->child_list));					//Initializing the current thread's child list
  struct thread *parentThread = thread_current();		//getting the parent thread
  sema_init(&t->parentChildSemaphore, 0);
  sema_init(&t->childwaitSemaphore,0);
  
  t->pThread = thread_current(); //Initializaing the current thread's parent..
  hash_init(&(t->memoryMapTable),MemoryMapTable_Hash_Func, MemoryMapTable_Less, NULL);
  hash_init(&(t->Supp_Page_Table), SuppPage_Table_Hash_Func, SuppPage_Table_Less, NULL);
  t->currentDirectory_sector  = ROOT_DIR_SECTOR ; 
  if(parentThread != NULL)	
{
			//checking for if the parent thread is not NULL
  list_push_back (&(parentThread->child_list), &(t->parent_elem));		//pushed the child thread into the parent thread 
}
  /*struct thread *t1 = getThreadFromTid(&(parentThread->child_list), tid);
  if(t1 != NULL)
  printf("id  %d\n",t1->tid); */
 /**/
  /* Add to run queue. */
  thread_unblock (t);
 // struct thread *t1 = getThreadFromTid(&(parentThread->child_list), tid);

  return tid;
}

/* Puts the current thread to sleep.  It will not be scheduled
   again until awoken by thread_unblock().

   This function must be called with interrupts turned off.  It
   is usually a better idea to use one of the synchronization
   primitives in synch.h. */
void
thread_block (void) 
{
  ASSERT (!intr_context ());
  ASSERT (intr_get_level () == INTR_OFF);

  thread_current ()->status = THREAD_BLOCKED;
  schedule ();
}

/* Transitions a blocked thread T to the ready-to-run state.
   This is an error if T is not blocked.  (Use thread_yield() to
   make the running thread ready.)

   This function does not preempt the running thread.  This can
   be important: if the caller had disabled interrupts itself,
   it may expect that it can atomically unblock a thread and
   update other data. */
void
thread_unblock (struct thread *t) 
{
  enum intr_level old_level;

  ASSERT (is_thread (t));

  old_level = intr_disable ();
  ASSERT (t->status == THREAD_BLOCKED);
  list_push_back (&ready_list, &t->elem);
  t->status = THREAD_READY;
  intr_set_level (old_level);
}

/* Returns the name of the running thread. */
const char *
thread_name (void) 
{
  return thread_current ()->name;
}

/* Returns the running thread.
   This is running_thread() plus a couple of sanity checks.
   See the big comment at the top of thread.h for details. */
struct thread *
thread_current (void) 
{
  struct thread *t = running_thread ();
  
  /* Make sure T is really a thread.
     If either of these assertions fire, then your thread may
     have overflowed its stack.  Each thread has less than 4 kB
     of stack, so a few big automatic arrays or moderate
     recursion can cause stack overflow. */
  ASSERT (is_thread (t));
  ASSERT (t->status == THREAD_RUNNING);

  return t;
}

/* Returns the running thread's tid. */
tid_t
thread_tid (void) 
{
  return thread_current ()->tid;
}

/* Deschedules the current thread and destroys it.  Never
   returns to the caller. */
void
thread_exit (void) 
{
  // PageFaultBad(&ready_list);
      thread_current()->isDead = true ;
  ASSERT (!intr_context ());
 
#ifdef USERPROG
 process_exit ();

#endif

  /* Just set our status to dying and schedule another process.
     We will be destroyed during the call to schedule_tail(). */
  intr_disable ();
  struct thread *t = thread_current();
 // printf("sema up called after exit  by thread with tid = %d\n", thread_current()->tid);

   // sema_up(&(t->parentChildSemaphore));
sema_up(&(t->childwaitSemaphore)); 
  // printf("after sema up called after exit  by thread with tid = %d\n", thread_current()->tid);
  thread_current ()->status = THREAD_DYING;

  
  schedule ();
  NOT_REACHED ();
}
void removeChildList(struct thread *t)
{

struct list *childList = &(t->child_list);
struct list_elem *currElem, *prevElem ;
struct thread *nextThread;
for (currElem = ((list_begin (childList))); currElem != list_end (childList);currElem = list_next (currElem))
	{ 
//                if(prevElem != NULL) list_remove(prevElem);
		if(currElem != NULL)
		{	
			
			prevElem = currElem ;			
		}	
		else break;
	}
if(prevElem != NULL) list_remove(prevElem);

}
/* Yields the CPU.  The current thread is not put to sleep and
   may be scheduled again immediately at the scheduler's whim. */
void
thread_yield (void) 
{
  struct thread *cur = thread_current ();
  enum intr_level old_level;
  
  ASSERT (!intr_context ());

  old_level = intr_disable ();
  if (cur != idle_thread) 
    list_push_back (&ready_list, &cur->elem);
  cur->status = THREAD_READY;
  schedule ();
  intr_set_level (old_level);
}

/* Sets the current thread's priority to NEW_PRIORITY. */
void
thread_set_priority (int new_priority) 
{
  thread_current ()->priority = new_priority;
}

/* Returns the current thread's priority. */
int
thread_get_priority (void) 
{
  return thread_current ()->priority;
}

/* Sets the current thread's nice value to NICE. */
void
thread_set_nice (int nice UNUSED) 
{
  /* Not yet implemented. */
}

/* Returns the current thread's nice value. */
int
thread_get_nice (void) 
{
  /* Not yet implemented. */
  return 0;
}

/* Returns 100 times the system load average. */
int
thread_get_load_avg (void) 
{
  /* Not yet implemented. */
  return 0;
}

/* Returns 100 times the current thread's recent_cpu value. */
int
thread_get_recent_cpu (void) 
{
  /* Not yet implemented. */
  return 0;
}

/* Idle thread.  Executes when no other thread is ready to run.

   The idle thread is initially put on the ready list by
   thread_start().  It will be scheduled once initially, at which
   point it initializes idle_thread, "up"s the semaphore passed
   to it to enable thread_start() to continue, and immediately
   blocks.  After that, the idle thread never appears in the
   ready list.  It is returned by next_thread_to_run() as a
   special case when the ready list is empty. */
static void
idle (void *idle_started_ UNUSED) 
{
  struct semaphore *idle_started = idle_started_;
  idle_thread = thread_current ();
  sema_up (idle_started);

  for (;;) 
    {
      /* Let someone else run. */
      intr_disable ();
      thread_block ();

      /* Re-enable interrupts and wait for the next one.

         The `sti' instruction disables interrupts until the
         completion of the next instruction, so these two
         instructions are executed atomically.  This atomicity is
         important; otherwise, an interrupt could be handled
         between re-enabling interrupts and waiting for the next
         one to occur, wasting as much as one clock tick worth of
         time.

         See [IA32-v2a] "HLT", [IA32-v2b] "STI", and [IA32-v3a]
         7.11.1 "HLT Instruction". */
      asm volatile ("sti; hlt" : : : "memory");
    }
}

/* Function used as the basis for a kernel thread. */
static void
kernel_thread (thread_func *function, void *aux) 
{
  ASSERT (function != NULL);

  intr_enable ();       /* The scheduler runs with interrupts off. */
  function (aux);       /* Execute the thread function. */
  thread_exit ();       /* If function() returns, kill the thread. */
}

/* Returns the running thread. */
struct thread *
running_thread (void) 
{
  uint32_t *esp;

  /* Copy the CPU's stack pointer into `esp', and then round that
     down to the start of a page.  Because `struct thread' is
     always at the beginning of a page and the stack pointer is
     somewhere in the middle, this locates the curent thread. */
  asm ("mov %%esp, %0" : "=g" (esp));
  return pg_round_down (esp);
}

/* Returns true if T appears to point to a valid thread. */
static bool
is_thread (struct thread *t)
{
  return t != NULL && t->magic == THREAD_MAGIC;
}

/* Does basic initialization of T as a blocked thread named
   NAME. */
static void
init_thread (struct thread *t, const char *name, int priority)
{
  ASSERT (t != NULL);
  ASSERT (PRI_MIN <= priority && priority <= PRI_MAX);
  ASSERT (name != NULL);

  memset (t, 0, sizeof *t);
  t->status = THREAD_BLOCKED;
  strlcpy (t->name, name, sizeof t->name);
  t->stack = (uint8_t *) t + PGSIZE;
  t->priority = priority;
  t->magic = THREAD_MAGIC;
  t->isDead = false ;
  t->isLoadedSuccess = false;
 // hash_init(&(t->memoryMapTable),MemoryMapTable_Hash_Func, MemoryMapTable_Less, NULL);
  
}

/* Allocates a SIZE-byte frame at the top of thread T's stack and
   returns a pointer to the frame's base. */
static void *
alloc_frame (struct thread *t, size_t size) 
{
  /* Stack data is always allocated in word-size units. */
  ASSERT (is_thread (t));
  ASSERT (size % sizeof (uint32_t) == 0);

  t->stack -= size;
  return t->stack;
}

/* Chooses and returns the next thread to be scheduled.  Should
   return a thread from the run queue, unless the run queue is
   empty.  (If the running thread can continue running, then it
   will be in the run queue.)  If the run queue is empty, return
   idle_thread. */
static struct thread *
next_thread_to_run (void) 
{
  if (list_empty (&ready_list))
    return idle_thread;
  else
    return list_entry (list_pop_front (&ready_list), struct thread, elem);
}

/* Completes a thread switch by activating the new thread's page
   tables, and, if the previous thread is dying, destroying it.

   At this function's invocation, we just switched from thread
   PREV, the new thread is already running, and interrupts are
   still disabled.  This function is normally invoked by
   thread_schedule() as its final action before returning, but
   the first time a thread is scheduled it is called by
   switch_entry() (see switch.S).

   It's not safe to call printf() until the thread switch is
   complete.  In practice that means that printf()s should be
   added at the end of the function.

   After this function and its caller returns, the thread switch
   is complete. */
void
schedule_tail (struct thread *prev) 
{
  struct thread *cur = running_thread ();
  
  ASSERT (intr_get_level () == INTR_OFF);

  /* Mark us as running. */
  cur->status = THREAD_RUNNING;
//printf("curent thread's tid %d\n%d",cur->tid,cur->status);
  /* Start new time slice. */
  thread_ticks = 0;

#ifdef USERPROG
  /* Activate the new address spacemulti-oom 1 
. */
  process_activate ();
#endif

  /* If the thread we switched from is dying, destroy its struct
     thread.  This must happen late so that thread_exit() doesn't
     pull out the rug under itself.  (We don't free
     initial_thread because its memory was not obtained via
     palloc().) */
  if (prev != NULL && prev->status == THREAD_DYING && prev != initial_thread) 
    {
      ASSERT (prev != cur);
	
	//printf("exiting thread's address %p \ntid %d\n status %d\n",prev,prev->tid,prev->status);
  //    printf("%d\n",prev->status);
    //  palloc_free_page (prev);
    }
}

/* Schedules a new process.  At entry, interrupts must be off and
   the running process's state must have been changed from
   running to some other state.  This function finds another
   thread to run and switches to it.

   It's not safe to call printf() until schedule_tail() has
   completed. */
static void
schedule (void) 
{
  struct thread *cur = running_thread ();
  struct thread *next = next_thread_to_run ();
  struct thread *prev = NULL;
//  printf("current thread id %d status %d\n",cur->tid, cur->status);
  ASSERT (intr_get_level () == INTR_OFF);
  ASSERT (cur->status != THREAD_RUNNING);
  ASSERT (is_thread (next));

  if (cur != next)
    prev = switch_threads (cur, next);
     //printf("after swapping next thread id %d status %d\n",next->tid, next->status); 
    schedule_tail (prev); 

}

/* Returns a tid to use for a new thread. */
static tid_t
allocate_tid (void) 
{
  static tid_t next_tid = 1;
  tid_t tid;

  lock_acquire (&tid_lock);
  tid = next_tid++;
  lock_release (&tid_lock);

  return tid;
}

/* Offset of `stack' member within `struct thread'.
   Used by switch.S, which can't figure it out on its own. */
uint32_t thread_stack_ofs = offsetof (struct thread, stack);


/*
struct thread *getThreadFromTid(struct list *tid_list , int child_tid)
{
struct list_elem *elem, *next;
struct thread *t;
  if (list_empty (tid_list))
    return NULL;
  elem = list_begin (tid_list);
  while ((next = list_next (elem)) != list_end (tid_list))
    { 	
	t = list_entry (next, struct thread, elem);
	if(t->tid == child_tid)
		{
			return t;
		}
    }	  
  return NULL ;
}
*/
/**/

struct thread *getThreadFromTid(struct list *tid_thread_list, int child_tid)
{
//printf("size %d",list_size(tid_thread_list));
struct list_elem *currElem ;struct thread *currThread ;
if (tid_thread_list == NULL || list_empty(tid_thread_list)) return NULL;
else
    {
	for (currElem = ((list_begin (tid_thread_list))); currElem != list_end (tid_thread_list); currElem = list_next (currElem))
	{
		
		//printf("thread %p id %d\n",currThread,currThread->tid);
		currThread = list_entry (currElem, struct thread,parent_elem);
		if(currThread != NULL)
		{		
			if(currThread->tid == child_tid)  
			return currThread ;
		}
		else break ;
	}
	return NULL;
     }
		
			



}

struct descriptorMap *getDescriptorMapPointerFromDescriptorTable(int fileDescriptor)
{
   struct list_elem *currElem ;
   struct descriptorMap *dMap;
   struct list *descriptorList = &(thread_current()->descriptor_table) ;
   if (!list_empty(descriptorList) && descriptorList != NULL)
     {
	for (currElem = ((list_begin (descriptorList))); currElem != list_end (descriptorList); currElem = list_next (currElem))
	{
                
		dMap = list_entry (currElem, struct descriptorMap, elem);
		if(dMap != NULL)
		{		
			if(dMap->fd == fileDescriptor)  
			return dMap ;
		}
		else break ;
	}
	
	
   }
	return NULL;
}
struct file *getFilePointerFromDescriptorTable(int fileDescriptor)
{
   struct descriptorMap *dMap = getDescriptorMapPointerFromDescriptorTable(fileDescriptor);
   if(dMap == NULL) return NULL ;
   if(dMap->is_File == true) return dMap->fileName;
	else
		return NULL;
}
struct descriptorMap *removeFilePointerFromDescriptorTable(int fileDescriptor)
{
   struct list_elem *currElem ;
   struct descriptorMap *dMap;
   struct list *descriptorList = &(thread_current()->descriptor_table) ;
   if (!list_empty(descriptorList) && descriptorList != NULL)
     {
	for (currElem = ((list_begin (descriptorList))); currElem != list_end (descriptorList); currElem = list_next (currElem))
	{
                
		dMap = list_entry (currElem, struct descriptorMap, elem);
		if(dMap != NULL)
		{		
			if(dMap->fd == fileDescriptor)  
			{
			  list_remove(currElem);
			 return dMap ;
			}
		}
		else break ;
	}
	
	
   }
	return NULL;
}
void list_pop_entry(struct list * , int);
void list_pop_entry(struct list *tid_thread_list, int child_tid)
{
	struct list_elem *currElem ;
	struct thread *t;
	  if (!list_empty(tid_thread_list) && tid_thread_list != NULL)
     {
	for (currElem = ((list_begin (tid_thread_list))); currElem != list_end (tid_thread_list); currElem = list_next (currElem))
	{
		t = list_entry (currElem, struct thread, elem);
		if(t != NULL)
		{		
			if(t->tid == child_tid)  
			{
			  list_remove(currElem);
			 return ;
			}
		}
		else break ;
	}
	
	
   }
	//return ;

}
/**/



