/*
 * Aliases resulted by context-insensitive and heap model in 255.vortex.
 * Author: Sen Ye
 * Date: 12/05/2014
 */
#include <stdlib.h>
#include "aliascheck.h"

typedef void *AddrType;
typedef AddrType addrtype;

typedef struct Ory
{
	addrtype *ChunkAddr;
} OryType;

OryType *Theory = NULL;

typedef struct Rectangle
{
	void (*draw) (int* p, float* q);
} Rectangle;

void Rectangle_draw(int* p, float* q) {}
addrtype Void_ExtendCore(long* p){}

void CoreMoreCore(addrtype *Region)
{
	long AllocCore1 = 0;
	*Region = (addrtype)Void_ExtendCore(&AllocCore1);
}

void MemNewOry()
{
	addrtype *ChunkAddrPtr = NULL;
	addrtype ChunkBlk = (addrtype)calloc(1,sizeof(addrtype));
	
	CoreMoreCore((addrtype*)(&Theory));

	if ((Theory->ChunkAddr = (addrtype*)ChunkBlk) != NULL)
	{
		ChunkAddrPtr = Theory->ChunkAddr;
		*ChunkAddrPtr = (addrtype)ChunkAddrPtr;
	}
}

void MemGetAddr(unsigned Chunk, unsigned index, addrtype *Addr)
{
	*Addr = *(((addrtype*)((Theory->ChunkAddr[Chunk])))+index);
}

void Object_GetImage(addrtype *This)
{
	unsigned chunk, index;
	MemGetAddr(chunk, index, This);
}

void Rectangle_new0()
{
	Rectangle* Image = NULL;
	Object_GetImage((addrtype*)&Image);
	Image->draw = Rectangle_draw;
}

void PartLib_Create(int **PrimalObj)
{
	Object_GetImage((addrtype *)PrimalObj);
}

int* PartLib01 = NULL;

int main()
{
	PartLib_Create(&PartLib01);
	NOALIAS(PartLib01, &Rectangle_draw);
	return 0;
}
