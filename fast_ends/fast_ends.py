def swap_ends(D):
	last = D.delete_last()
	first = D.delete_first()
	D.insert_first(last)
	D.insert_last(first)


# 0, 1, 2, 3, ..., k, k + 1, k + 2, ..., n
# k + 1, k + 2, ..., n, 0, 1, 2, 3, ..., k
def shift_left(D, k):
	if k <= 0:
		return	
	first = D.delete_first()
	D.insert_last(first)
	shift_left(D, k - 1)