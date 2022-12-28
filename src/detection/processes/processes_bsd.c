#include "processes.h"

#include <sys/sysctl.h>
#ifdef __FreeBSD__
    #include <sys/types.h>
    #include <sys/user.h>
#endif

uint32_t ffDetectProcesses(FFstrbuf* error)
{
    int request[] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL};
    size_t length;

    if(sysctl(request, sizeof(request) / sizeof(*request), NULL, &length, NULL, 0) != 0)
    {
        ffStrbufAppendS(error, "sysctl() failed");
        return 0;
    }
    return (uint32_t)(length / sizeof(struct kinfo_proc));
}
