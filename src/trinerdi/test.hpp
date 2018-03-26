/* Returns a random ll */
ll llrand() {
	return (((ll)lrand48()) << 31) + lrand48();
}
