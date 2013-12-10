#ifndef MultiTasker_hh
#define MultiTasker_hh 1

#include <queue>
#include <pthread.h>
#include <iostream>
#include "RLException.hh"


#include "VerbosePrinter.hh"
#include "VerbosePrinterEventEnabled.hh"

using namespace std;


/**Used for running certain multi-threaded tasks.

 */
template<class Tin, class Tout>
class MultiTasker : public VerbosePrinterEventEnabled
{
private:
  struct ThreadEssentials
  {
    pthread_mutex_t * input_LOCK; ///Mutex for preventing multiple access to the input object.
    pthread_mutex_t * output_LOCK; ///Mutex for preventing multiple access to the output object.
    pthread_mutex_t * Terminate_LOCK; ///Mutex for preventing multiple access to the terminating boolean.
    pthread_mutex_t * InputMinusOutput_LOCK; ///Mutex for preventing multiple access to the InputMinusOutput number.
    bool * TerminateWorkers; /// Used to instruct worker threads to self-terminate when we have no more work.
    queue<Tin> * input; ///Pointer to the directory names queue.
    queue<Tout> * output; ///Pointer to the result queue.
    int MaxOutputSize; ///Maximum output size.
    unsigned long long * InputMinusOutput;
    Tout (*myDoWorkFunction)(Tin); ///Function pointer to the DoWork function.
  };

public:
  MultiTasker(Tout (*DoWorkFunction)(Tin), ///Function pointer to the function that does the actual work. 
		  unsigned int nbrOfThreads = 10 /// Number of threads used.
		  );

  ~MultiTasker(); ///Destructor.

  void LimitOutputQueueSize(int newSize ///New size.
			    ); ///Set maximum number of elements inoutput queue. Negative number means no limit.

private: 
  template<typename T>
  static void delete_if_pointer(T myT ///Non pointer type object.
				); ///Used to selectively delete only pointers. Choice made at compile time.
  template<typename T>
  static void delete_if_pointer(T*& myT ///Pointer to object.
				); ///Used to selectively delete only pointers. Choice made at compile time.
  
  static void * DoWork(void * ptr ///Pointer to some object (in this case a ThreadEssentials)
		       ); /// The thread work function.
public:
  
  void LaunchThreads(); ///Launch worker threads, if they are not running. If they are, nothing will happen.
  void DestroyThreads(); ///Instructs worker threads to terminate, and waits for them to finish the currently queued work.
  void AddInput(Tin value ///The input.
		); ///Adds input (=work to do)
  Tout GetOutput(); ///Retrieves output and returns it. Check if there is output by GetOutputSize. Will pause execution until output is generated, if necessary.
  unsigned int GetOutputSize(); ///Returns the number of output objects waiting to be retreived. 
  unsigned int GetInputSize(); ///Returns the number of input objects waiting to be processed. 
  unsigned long long GetInputMinusOutput(); /// Self-descriptive.
  void PauseUntilOutputIsGenerated(); ///Pause until output is generated. If there is none to produce, however, we return to avoid deadlocks and other unpleasant stuff.
private:
  unsigned int threads; ///Number of threads to use.
  
  unsigned long long InputMinusOutput; /// The input minus the output. Used to keep track of when there is no more work to do. WARNING: USE MUTEX

  queue<Tin>  input; /// Queue where input ("work to be processed") is stored. WARNING: USE MUTEX

  queue<Tout> output; /// Queue where output ("work done") is stored. WARNING: USE MUTEX

  Tout (*myDoWorkFunction)(Tin); ///Function pointer to the DoWork function.
  pthread_mutex_t input_LOCK; ///Mutex for preventing multiple access to the input object.
  pthread_mutex_t output_LOCK; ///Mutex for preventing multiple access to the output object.
  pthread_mutex_t Terminate_LOCK; ///Mutex for preventing multiple access to the terminating boolean.
  pthread_mutex_t InputMinusOutput_LOCK; ///Mutex for preventing multiple access to the InputMinusOutput integer.

  pthread_attr_t attr; /// Attributes for the threads.

  bool TerminateWorkers; ///Instruct worker threads to terminate. WARNING: USE MUTEX

  queue<pthread_t *> myThreads; /// Threads currently running.

  int MaxOutputSize; /// Used to prevent output from overflowing. 


  static inline bool ThreadSafeShouldPauseCheck(ThreadEssentials * myEssentials ///Essential pointers for parallell work.
						); ///Self-descriptive.

  static inline bool ThreadSafeTerminateCheck(ThreadEssentials * myEssentials ///Essential pointers for parallell work.
					      ); ///Self-descriptive.

  static inline void TerminateThreadSafely(ThreadEssentials * myEssentials ///Essential pointers for parallell work.
					   );///Self-descriptive.

  static void ThreadSafeIdleAndLock(ThreadEssentials * myEssentials ///Essential pointers for parallell work.
				    );///Self-descriptive.

  template<typename T>
  static bool TypeIsVoid (T myT ///Possibly void object.
				); ///Used to check if a type is void.
  template<typename T>
  static bool TypeIsVoid (void * myT ///Possibly void object.
				); ///Used to check if a type is void.


  template<typename T>
  static bool TypeIsNullPointer (T myT ///Possibly void object.
				); ///Used to check if a type is a null pointer.


  template<typename T>
  static bool TypeIsNullPointer (T*& myT ///Possibly void object.
				); ///Used to check if a type is a null pointer.
};
















//We have to include the implementation in the header too, since this is a template class.

//////// BEGIN IMPLEMENTATION

template<class Tin, class Tout>
MultiTasker<Tin, Tout>::MultiTasker(Tout (*DoWorkFunction)(Tin),unsigned int nbrOfThreads)
{
  threads = nbrOfThreads;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  pthread_mutex_init(&input_LOCK, NULL);
  pthread_mutex_init(&output_LOCK, NULL);
  pthread_mutex_init(&InputMinusOutput_LOCK, NULL);
  pthread_mutex_init(&Terminate_LOCK, NULL);
  TerminateWorkers = false;
  MaxOutputSize = -1; // No limit.
  InputMinusOutput = 0;
  myDoWorkFunction = DoWorkFunction;
}

template<class Tin, class Tout>
MultiTasker<Tin, Tout>::~MultiTasker()
{
  DestroyThreads(); //Last resort
  pthread_attr_destroy(&attr);
  pthread_mutex_destroy(&input_LOCK);
  pthread_mutex_destroy(&output_LOCK);
  pthread_mutex_destroy(&InputMinusOutput_LOCK);
  pthread_mutex_destroy(&Terminate_LOCK);
}

template<class Tin, class Tout>
void MultiTasker<Tin, Tout>::LimitOutputQueueSize(int newSize)
{
  MaxOutputSize = newSize;
}

template<class Tin, class Tout>
template<typename T>
void MultiTasker<Tin, Tout>::delete_if_pointer(T myT)
{
  //If it is not a pointer (this function is called), do nothing.
}

template<class Tin, class Tout>
template<typename T>
void MultiTasker<Tin, Tout>::delete_if_pointer(T*& myT) 
{
  delete myT; //If it is a pointer, delete it
}

template<class Tin, class Tout>
template<typename T>
bool MultiTasker<Tin, Tout>::TypeIsNullPointer(T myT) 
{
  return false;
}

template<class Tin, class Tout>
template<typename T>
bool MultiTasker<Tin, Tout>::TypeIsNullPointer(T*& myT) 
{
  return myT == NULL;
}


template<class Tin, class Tout>
template<typename T>
bool MultiTasker<Tin, Tout>::TypeIsVoid(T myT)
{
  return false;
}

template<class Tin, class Tout>
template<typename T>
bool MultiTasker<Tin, Tout>::TypeIsVoid(void * myT)
{
  return true;
}


template<class Tin, class Tout>
void * MultiTasker<Tin, Tout>::DoWork(void * ptr)
{
  ThreadEssentials * myEssentials = (ThreadEssentials*) ptr;
  
  while(true)
    {
      ThreadSafeIdleAndLock(myEssentials); /////////// Wait until there is work to do, or the thread should exit.
      pthread_mutex_lock (myEssentials->input_LOCK); /////////// MUTEX UNLOCK	
      
      Tin myInput = myEssentials->input->front();
      myEssentials->input->pop();

      pthread_mutex_unlock (myEssentials->input_LOCK); /////////// MUTEX UNLOCK
      
      Tout myOutput = (*myEssentials->myDoWorkFunction)(myInput);
      
      delete_if_pointer<Tin>(myInput);

      if(!TypeIsNullPointer(myOutput) && !TypeIsVoid(myOutput) ) ///Don't queue up null stuff.
		{
		  pthread_mutex_lock (myEssentials->output_LOCK); /////////// MUTEX UNLOCK
		  myEssentials->output->push(myOutput);
		  pthread_mutex_unlock (myEssentials->output_LOCK); /////////// MUTEX UNLOCK
		}
      else
		{
		  pthread_mutex_lock (myEssentials->InputMinusOutput_LOCK); /////////// MUTEX UNLOCK
		  --(*myEssentials->InputMinusOutput); // If we don't add output, we still need to keep it balanced.
		  pthread_mutex_unlock (myEssentials->InputMinusOutput_LOCK); /////////// MUTEX UNLOCK
		}
    }
  return (void*)NULL; ///This should never happen.
}

template<class Tin, class Tout>
void MultiTasker<Tin, Tout>::LaunchThreads() ///Launch worker threads, if they are not running. If they are, nothing will happen.
{
  while(myThreads.size() < threads) ///If we lack threads, launch a couple of them...
    {
      vPrint(10,"Dispatching worker thread.\n");
      pthread_t * myOneThread = new pthread_t();
      
      ThreadEssentials * myThreadEssentials = new ThreadEssentials();
      myThreadEssentials->input_LOCK = &input_LOCK;
      myThreadEssentials->output_LOCK = &output_LOCK;
      myThreadEssentials->Terminate_LOCK = &Terminate_LOCK;
      myThreadEssentials->InputMinusOutput_LOCK = &InputMinusOutput_LOCK;
      myThreadEssentials->TerminateWorkers = &TerminateWorkers;
      myThreadEssentials->input = &input;
      myThreadEssentials->output = &output;
      myThreadEssentials->MaxOutputSize = MaxOutputSize;
      myThreadEssentials->myDoWorkFunction = myDoWorkFunction;
      myThreadEssentials->InputMinusOutput = &InputMinusOutput;
      //Ownership passed on.
      
      int ret = pthread_create(myOneThread, &attr, DoWork, 
			       myThreadEssentials);
      if(ret!=0)
	throw RLException("Error while creating thread.");
      myThreads.push(myOneThread);
    }
}

template<class Tin, class Tout>
void MultiTasker<Tin, Tout>::DestroyThreads() ///Instructs worker threads to terminate, and waits for them to finish.
{
  vPrint(10, "Instructing threads to terminate ASAP.\n");
  bool empty = myThreads.empty();
  pthread_mutex_lock (&Terminate_LOCK); //////////MUTEX LOCK
  TerminateWorkers = true;
  pthread_mutex_unlock(&Terminate_LOCK); /////////MUTEX UNLOCK
  
  while(!myThreads.empty())
    {
      vPrint(10,"Waiting for thread to finish.\n");
      pthread_join(*(myThreads.front()), NULL);
      delete myThreads.front();
      myThreads.pop();
    }
  if(!empty)
    vPrint(10,"Threads terminated successfully.\n");
}

template<class Tin, class Tout>
void MultiTasker<Tin, Tout>::AddInput(Tin value)
{
  pthread_mutex_lock (&input_LOCK); //////////MUTEX LOCK
  input.push(value);
  pthread_mutex_unlock (&input_LOCK); //////////MUTEX UNLOCK
  pthread_mutex_lock (&InputMinusOutput_LOCK); //////////MUTEX LOCK
  ++InputMinusOutput;
  pthread_mutex_unlock (&InputMinusOutput_LOCK); //////////MUTEX UNLOCK
}

template<class Tin, class Tout>
Tout MultiTasker<Tin, Tout>::GetOutput() 
{
  if(myThreads.size() < threads)
    LaunchThreads(); // Failsafe.
  PauseUntilOutputIsGenerated();
  pthread_mutex_lock (&output_LOCK); //////////MUTEX LOCK
  Tout toReturn = output.front();
  output.pop();
  pthread_mutex_unlock (&output_LOCK); //////////MUTEX UNLOCK
  pthread_mutex_lock (&InputMinusOutput_LOCK); //////////MUTEX LOCK
  --InputMinusOutput;
  pthread_mutex_unlock (&InputMinusOutput_LOCK); //////////MUTEX UNLOCK
  return toReturn;
}

template<class Tin, class Tout>
unsigned int MultiTasker<Tin, Tout>::GetOutputSize() ///Returns the number of output objects waiting to be retreived. 
{
  pthread_mutex_lock (&output_LOCK); //////////MUTEX LOCK
  unsigned int outputSize = output.size();
  pthread_mutex_unlock (&output_LOCK); //////////MUTEX UNLOCK
  return outputSize;
}

template<class Tin, class Tout>
unsigned int MultiTasker<Tin, Tout>::GetInputSize() ///Returns the number of input objects waiting to be processed. 
{
  pthread_mutex_lock (&input_LOCK); //////////MUTEX LOCK
  unsigned int inputSize = input.size();
  pthread_mutex_unlock (&input_LOCK); //////////MUTEX UNLOCK
  return inputSize;
}

template<class Tin, class Tout>
unsigned long long MultiTasker<Tin, Tout>::GetInputMinusOutput() /// Self-descriptive.
{
  unsigned long long toReturn;
  pthread_mutex_lock (&InputMinusOutput_LOCK); //////////MUTEX LOCK
  toReturn = InputMinusOutput;
  pthread_mutex_unlock (&InputMinusOutput_LOCK); //////////MUTEX UNLOCK
  return toReturn;
}

template<class Tin, class Tout>
void MultiTasker<Tin, Tout>::PauseUntilOutputIsGenerated() ///Pause until output is generated. If there is none to produce, however, we return to avoid deadlocks and other unpleasant stuff.
{
  pthread_mutex_lock (&InputMinusOutput_LOCK); //////////MUTEX LOCK
  long long local = InputMinusOutput;
  pthread_mutex_unlock (&InputMinusOutput_LOCK); //////////MUTEX UNLOCK

  while(GetOutputSize() == 0 && local != 0)
    {
      usleep(3000);
      pthread_mutex_lock (&InputMinusOutput_LOCK); //////////MUTEX LOCK
      local = InputMinusOutput;
      pthread_mutex_unlock (&InputMinusOutput_LOCK); //////////MUTEX UNLOCK
    }
}

template<class Tin, class Tout>
bool MultiTasker<Tin, Tout>::ThreadSafeShouldPauseCheck(ThreadEssentials * myEssentials)
{
  pthread_mutex_lock (myEssentials->input_LOCK); //////////MUTEX LOCK
  bool empty = myEssentials->input->empty();
  pthread_mutex_unlock (myEssentials->input_LOCK); //////////MUTEX UNLOCK
  pthread_mutex_lock (myEssentials->output_LOCK); //////////MUTEX LOCK
  bool overflow = ((int)myEssentials->output->size() >= myEssentials->MaxOutputSize) && (myEssentials->MaxOutputSize > 0);
  pthread_mutex_unlock (myEssentials->output_LOCK); //////////MUTEX UNLOCK
  return empty || overflow;
}

template<class Tin, class Tout>
bool MultiTasker<Tin, Tout>::ThreadSafeTerminateCheck(ThreadEssentials * myEssentials)
{
  pthread_mutex_lock (myEssentials->Terminate_LOCK); //////////MUTEX LOCK
  bool terminate = *(myEssentials->TerminateWorkers);
  pthread_mutex_unlock (myEssentials->Terminate_LOCK); //////////MUTEX UNLOCK
  return terminate;
}

template<class Tin, class Tout>
void MultiTasker<Tin, Tout>::TerminateThreadSafely(ThreadEssentials * myEssentials)
{
  delete myEssentials;
  pthread_exit((void*)NULL);
}

template<class Tin, class Tout>
void MultiTasker<Tin, Tout>::ThreadSafeIdleAndLock(ThreadEssentials * myEssentials)
{
  bool willpause = ThreadSafeShouldPauseCheck(myEssentials);
  if(ThreadSafeTerminateCheck(myEssentials))
    TerminateThreadSafely(myEssentials);
  
  while(willpause)
    {
      usleep(5000);
      if(ThreadSafeTerminateCheck(myEssentials))
	TerminateThreadSafely(myEssentials);
      willpause = ThreadSafeShouldPauseCheck(myEssentials);
    }
  return;
}




#endif
