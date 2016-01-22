#include "hmms.hpp"

// ~ List<HMMTemplate*>

template<>
void kernel::std::List<kernel::memory::HMMTemplate*>::PushFirstElement(kernel::memory::HMMTemplate * const &data)
{
    static Node new_first(data, 0, nullptr, list_first);
    list_first = &new_first;
    list_size += sizeof(Node);
    list_count++;
}

// ~ HeapMemoryManagerServer
using namespace kernel;

bool HeapMemoryManagerServer::RegisterManager(memory::HMMTemplate *new_hmm)
{
    if(new_hmm == nullptr)
        return false;

    if(kernel_hmm == nullptr)
    {
        hmms.PushFirstElement(new_hmm);
        kernel_hmm = new_hmm;
        return true;
    }

    hmms.PushLastElement(new_hmm);

    if(current_hmm == nullptr)
        current_hmm = new_hmm;

    return true;
}

bool HeapMemoryManagerServer::UnregisterManager(memory::HMMTemplate *old_hmm)
{
    if(old_hmm == nullptr)
        return false;

    hmms.RemoveElement(old_hmm);

    if(kernel_hmm == old_hmm)
        kernel_hmm = hmms.GetFirstElement();

    if(current_hmm = old_hmm)
        current_hmm = kernel_hmm;

    return true;
}
