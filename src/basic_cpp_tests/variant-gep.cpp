/*
	FIObjPN:
	
		memobj pointed by ptr is a FIObjPN, which represents a struct Data object.
		(1)
		wpa -fspta -dump-consG -detect-tc -svf-main -stat=false -print-all-pts ./cast.opt
		(2)
		wpa -nander -dump-consG -detect-tc -svf-main -stat=false -print-all-pts ./cast.opt
 */

struct Point{	
	int x;
	int y;			
};
struct D3Point:public Point{
	int z;
};
struct Data{	
	int d;
	int a;
	int t;
	Point p;

};


int main(int argc, char * argv[]){	
	Data *dt = new Data[16];
	
	Point * ptr = &dt[argc].p;
	D3Point * c = static_cast<D3Point*>(ptr);
	
	ptr = &dt[3].p;
	c = static_cast<D3Point*>(ptr);
}


