
#include "MemoryStream.h"
#include "KBDebug.h"
#include "ObjectPool.h"

static ObjectPool<MemoryStream> _g_memoryStreamPool;

MemoryStream* MemoryStream::createObject()
{
	return _g_memoryStreamPool.createObject();
}

void MemoryStream::reclaimObject(MemoryStream* obj)
{
	obj->clear(false);
	_g_memoryStreamPool.reclaimObject(obj);
}

void MemoryStream::print_storage()
{
	FString fbuffer;
	uint32 trpos = rpos_;

	DEBUG_MSG("MemoryStream::print_storage(): STORAGE_SIZE: %lu, rpos=%lu.", (unsigned long)wpos(), (unsigned long)rpos());

	for (uint32 i = rpos(); i < wpos(); ++i)
	{
		fbuffer.AppendInt((int)read<uint8>(i));
		fbuffer += TEXT(" ");
	}

	DEBUG_MSG("%s", *fbuffer);

	rpos_ = trpos;
}