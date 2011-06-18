#include <CoreFoundation/CoreFoundation.h>

#include "radat.h"

static int t_sock;
static int t_len;

void timerCallBack(CFRunLoopTimerRef timer, void *info);

void timerCallBack(CFRunLoopTimerRef timer, void *info)
{
  send_pack(t_sock, t_len);
  incr_ident();
}

void start_timed_send(int _sock, int _len, double interval /* seconds */, int repetitions)
{
  t_sock = _sock;
  t_len = _len;

  CFRunLoopTimerRef runLoopTimer = CFRunLoopTimerCreate(
							kCFAllocatorDefault,              // allocator
							CFAbsoluteTimeGetCurrent() + interval, // fire date (now)
							interval,           // fire interval (0 or -ve means a one-shot timer)
							0,             // flags (ignored)
							0,             // order (ignored)
							timerCallBack, // called when the timer fires
							NULL);         // context

  CFRunLoopAddTimer(CFRunLoopGetCurrent(),  // the run loop to use
		    runLoopTimer,           // the run-loop timer to add
		    kCFRunLoopDefaultMode); // add timer to this mode

  CFRunLoopRunInMode(kCFRunLoopDefaultMode, // run it in this mode
		     interval * repetitions,    // run it for this long
		     false); // exit after processing one source?

  CFRunLoopTimerInvalidate(runLoopTimer);
  CFRelease(runLoopTimer);
}
