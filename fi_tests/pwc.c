/*
 * PWC cycle.
 * Author: Sen Ye
 * Date: 30/01/2014
 * Description: 181.mcf/mcfutil.c, flow_cost
 */
#include <stdio.h>

typedef struct arc
{
	struct arc *nextout, *nextin;
	long ident;
} arc_t;


typedef struct network
{
	arc_t *arcs, *stop_arcs;
	arc_t *dummy_arcs, *stop_dummy; 
} network_t;

int main()
{
	network_t *net;
	arc_t *arc;
	void *stop;
	int condition;

	stop = (void *)net->stop_arcs;
	for( arc = net->arcs; arc != (arc_t *)stop; arc++ )	{
		if( arc->ident ) {
			if( condition ) 
				printf("hello world\n");
		}
	}
	return 0;
}
