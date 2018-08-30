int readline(int fd, char *buf, int nbytes);
void ising_initialize_data(real_t g, size_t myN, size_t myK, real_t Texp, real_t *J, bool *s);
real_t vectornormone(real_t *J, size_t size);
real_t vectornormtwo(real_t *J, size_t length);
