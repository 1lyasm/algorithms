import numpy as np

n = 3

A1 = np.random.randint(1, 6, size = (n, n + 1))
A2 = A1.copy()

def print_matrix(matrix):
    for i in range(len(matrix)):
        print(matrix[i])
    print("\n")

print("Original code:\n\n")

print("Initially:\n\n")
print_matrix(A1)
for i in range(0, n - 1):
    for j in range(i + 1, n):
        for k in range(i, n + 1):
            A1[j][k] = A1[j][k] - A1[i][k] * A1[j][i] / A1[i][i]
            # print_matrix(A)

print("Result:\n\n")
print_matrix(A1)



print("Original code:\n\n")

print("Initially:\n\n")
print_matrix(A2)

for i in range(1, n):
    for j in range(0, i):
        A2[i][j] = 0

print("Result:\n\n")
print_matrix(A2)

print(np.array_equal(A1, A2))
