
void a();
void b();

void d(){

	a();
}

void c(){

	b();
	d();
}

void b(){

	c();

}

void a(){

	b();

}

int main(){

	a();

}
