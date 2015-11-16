void D(char ***ppp) { ***ppp = 0; }

void C(char ***ppp) { ***ppp = 0; }

void B(char ***ppp) { D(ppp); }

void A() {
  char c;
  char *p = &c;
  char **pp = &p;
  B(&pp);
  C(&pp);
} 
