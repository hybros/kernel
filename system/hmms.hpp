#ifndef __HEAP_MEMORY_MANAGER__
#define __HEAP_MEMORY_MANAGER__

#include "../std/data_types.hpp"
#include "../std/bitmap.hpp"
#include "../memory/hmm_temp.hpp"
#include "../std/list.hpp"

namespace kernel
{
namespace std
{

template<> void List<memory::HMMTemplate*>::PushFirstElement(memory::HMMTemplate * const &data);

}

class HeapMemoryManagerServer
{
public:
    inline HeapMemoryManagerServer();
    inline ~HeapMemoryManagerServer();

    bool RegisterManager(memory::HMMTemplate *new_hmm);
    bool UnregisterManager(memory::HMMTemplate *old_hmm);

    inline memory::HMMTemplate *GetManager(uint &hmm_id);
    inline uint GetManagerID(memory::HMMTemplate *searched_hmmm);                     // just list position
    inline memory::HMMTemplate *GetCurrentManager();
    inline uint GetCurrentManagerID();
    inline void LoadCurrentManager(uint &new_current_hmm_id);

    inline void *AllocateMemory(size_t memory_size);
    inline void FreeMemory(void *memory_address);

    inline memory::HMMTemplate *GetKernelHMM();

private:
    memory::HMMTemplate *kernel_hmm;
    memory::HMMTemplate *current_hmm;
    std::List<memory::HMMTemplate*> hmms;
};
typedef class HeapMemoryManagerServer HMMServer;

// ~ HeapMemoryManager

HeapMemoryManagerServer::HeapMemoryManagerServer() : kernel_hmm(nullptr), current_hmm(nullptr) {}

HeapMemoryManagerServer::~HeapMemoryManagerServer()
{
    kernel_hmm = current_hmm = nullptr;
    hmms.Clear();
}

memory::HMMTemplate *HeapMemoryManagerServer::GetManager(uint &hmm_id)
{
    return hmms.GetElement(hmm_id);
}

uint HeapMemoryManagerServer::GetManagerID(memory::HMMTemplate *searched_hmmm)
{
    return hmms.GetPosition(searched_hmmm);
}

memory::HMMTemplate *HeapMemoryManagerServer::GetCurrentManager()
{
    return current_hmm;
}

uint HeapMemoryManagerServer::GetCurrentManagerID()
{
    return hmms.GetPosition(current_hmm);
}

void HeapMemoryManagerServer::LoadCurrentManager(uint &new_current_hmm_id)
{
    current_hmm = hmms.GetElement(new_current_hmm_id);
}

void *HeapMemoryManagerServer::AllocateMemory(size_t memory_size)
{
    return current_hmm->AllocateMemory(memory_size);
}

void HeapMemoryManagerServer::FreeMemory(void *memory_address)
{
    current_hmm->FreeMemory(memory_address);
}

memory::HMMTemplate *HeapMemoryManagerServer::GetKernelHMM()
{
    return kernel_hmm;
}

}

#endif
