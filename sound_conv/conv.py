# Dosyanin calismasi icin numpy, termcolor, matplotlib.pyplot,
# sounddevice, ve soundfile kutuphanelerini "pip install" yapiniz
import numpy as np
from termcolor import colored
import matplotlib.pyplot as plt
import sounddevice as sd
import soundfile as sf

# 1
print("Soru 1\n")

def input_sig(name):
    n = int(input(f"{name} dizisinin boyutu: "))
    sig = np.empty(n)
    for i in range(n):
        sig[i] = float(input(f"{name}[{i}]: "))
    zero_idx = int(input(f"{name}-in sıfır noktası: "))
    print("\n")
    return sig, n, zero_idx

x, n, xzero = input_sig("x")
y, m, yzero = input_sig("y")

def print_sig(sig, len_, zero_idx, name):
    print(f"{name} sinyali: [ ", end="")
    for i in range(len_):
        elem = round(sig[i], 3)
        if i == zero_idx:
            print(colored(elem, "red"), end=" ")
        else: print(elem, end=" ")
    print(" ]")

print_sig(x, n, xzero, "x")
print_sig(y, m, yzero, "y")

def sparse_dot(full=None, full_start=None, sparse=None,
               sparse_start=None, nonzero_idx_lst=None):
    sum, idx = 0, 0
    while nonzero_idx_lst[idx] < sparse_start:
        idx += 1
    start_dif = full_start - sparse_start
    while idx <= nonzero_idx_lst.size - 1:
        nonzero_idx = nonzero_idx_lst[idx]
        if (nonzero_idx + start_dif >= full.size):
            break
        sum += full[nonzero_idx + start_dif] * sparse[nonzero_idx]
        idx += 1
    return sum

def find_nonzero_idx_lst(arr):
    nonzero_idx_lst = np.empty(0, dtype=int)
    for i in range(len(arr)):
        if arr[i] != 0:
            nonzero_idx_lst = np.append(nonzero_idx_lst, np.array([i]))
    return nonzero_idx_lst

def myConv(x, n, y, m):
    s = np.empty(n + m - 1)
    if (n < m): x, y, m, n = y, x, n, m
    y_flipped = np.array(y.tolist()[::-1])
    nonzero_idx_lst = find_nonzero_idx_lst(y_flipped)
    xs, ys = 0, len(y_flipped) - 1
    for i in range(n + m - 1):
        s[i] = sparse_dot(full=x, full_start=xs, sparse=y_flipped,
            sparse_start=ys, nonzero_idx_lst=nonzero_idx_lst)
        xs, ys = xs + (m - 1 <= i <= n - 2) + (i >= n - 1), ys - (i <= m - 2)
    return s

out_zero = xzero + yzero
out_sig = myConv(x, n, y, m)
len_sig = len(out_sig)
print_sig(out_sig, len_sig, out_zero, "Çıkış")

# 2
print("\nSoru 2\n")

x1, y1 = [6, 4, 1, 2, 3], [1, 2, 3, 5]
x1, y1 = np.array(x1), np.array(y1)
x1zero, y1zero = 2, 0

x2, y2 = [5, 7, 6, 0], [1, 4, 2, 1, 3]
x2, y2 = np.array(x2), np.array(y2)
x2zero, y2zero = 1, 4

def comp_convs(x, n, y, m):
    return myConv(x, n, y, m), np.convolve(x, y)

out_sig1, out_sig_np1, out_sig2, out_sig_np2 = \
    *comp_convs(x1, len(x1), y1, len(y1)), *comp_convs(x2, len(x2), y2, len(y2))

fig, axs = plt.subplots(nrows=4, ncols=2, figsize=(12, 8),
    num="İki veri setinde konvolüsyon karşılaştırması", sharex=True)
pad1, pad2 = 8, 10.5
xy = (0.5, 1)
axs[0][0].annotate("Veri seti 1", xy=xy, xytext=(-1.5, pad1),
    fontweight="extra bold", fontsize="xx-large")
axs[0][1].annotate("Veri seti 2", xy=xy, xytext=(-1.5, pad2),
    fontweight="extra bold", fontsize="xx-large")

def graphical_compare(x_param, y_param, out_sig, out_sig_np, fig, axis):
    x, xzero, xname = x_param
    y, yzero, yname = y_param
    n, m = len(x), len(y)
    zero_idx = xzero + yzero
    tx, ty = (list(range(-xzero, -xzero + n))), (list(range(-yzero, -yzero + m)))
    t_out = np.array(list(range(0, len(out_sig))), dtype=int) - zero_idx

    axis[0].locator_params("x", integer=True, tight=True)

    for i in axis:
        i.axvline(linewidth=2, color="k")
        i.axhline(linewidth=2, color="k")

    axis[0].stem(tx, x, markerfmt="ro", linefmt="k-", basefmt=" ")
    axis[0].set_title(f'{xname} sinyali')

    axis[1].stem(ty, y, markerfmt="bo", linefmt="k-", basefmt=" ")
    axis[1].set_title(f'{yname} sinyali')

    
    axis[0].set_yticks(x)
    axis[1].set_yticks(y)
    axis[2].set_yticks(out_sig)
    axis[3].set_yticks(out_sig_np)

    axis[2].stem(t_out, out_sig, markerfmt="ko", linefmt="k-", basefmt=" ")
    axis[2].set_title('myConv')

    axis[3].stem(t_out, out_sig_np, markerfmt="go", linefmt="k-", basefmt=" ")
    axis[3].set_title('np.convolve')

    for i in axis:
        plt.setp(i.get_xticklabels(), visible=False)

graphical_compare((x1, x1zero, "x1"), (y1, y1zero, "y1"),
    out_sig1, out_sig_np1, fig, axs[:, 0])
graphical_compare((x2, x2zero, "x2"), (y2, y2zero, "y2"),
    out_sig2, out_sig_np2, fig, axs[:, 1])

def textual_compare(x_param, y_param, out_sig, out_sig_np):
    x, xzero, xname = x_param
    y, yzero, yname = y_param
    zero_idx = xzero + yzero
    n, m = len(x), len(y)
    print_sig(x, n, xzero, xname)
    print_sig(y, m, yzero, yname)
    print("\n")
    print_sig(out_sig, len(out_sig), zero_idx, "myConv çıkışı")
    print_sig(out_sig_np, len(out_sig_np), zero_idx, "np.convolve çıkışı")
    print("\n")

print("Veri seti 1: \n")
textual_compare((x1, x1zero, "x1"), (y1, y1zero, "y1"),
    out_sig1, out_sig_np1)
print("Veri seti 2: \n")
textual_compare((x2, x2zero, "x2"), (y2, y2zero, "y2"),
    out_sig2, out_sig_np2)

plt.show()

# 3
print("Soru 3\n")

NCHANNELS = 1
RATE = 44100
SHORT_DUR, LONG_DUR = 5, 10

def rec_play(duration):
    rec_ = sd.rec(frames=duration * RATE, samplerate=RATE,
        channels=NCHANNELS, dtype=np.int32)
    print(f"{duration} saniyelik ses kaydı başlıyor")
    sd.wait()
    print(f"{duration} saniyelik ses kaydı bitti", "\n")
    return rec_

X1 = np.squeeze(rec_play(SHORT_DUR))
print("\n")
X2 = np.squeeze(rec_play(LONG_DUR))
sf.write("five.wav", X1, RATE)
sf.write("ten.wav", X2, RATE)
print("Kısa kaydın yapısı ", X1.shape)
print("Uzun kaydın yapısı: ", X2.shape)

# 4
print("\nSoru 4\n")

myY1 = np.empty(3, dtype=object)
Y1 = np.empty(3, dtype=object)
myY2 = np.empty(3, dtype=object)
Y2 = np.empty(3, dtype=object)

A = 0.8
M_MIN, M_MAX = 2, 4
GAP = 400
KERNEL_SIZE = M_MAX * GAP + 1

# Sonuc sesleri seslendirmek icin normallestirme yapilmasi gerekiyor, 
# onun icin np.max ve np.abs kullandim. Konvolusyona ait olmadigi icin  
# hazir fonksiyon kullaniyorum fakat basit fonksiyonlar, kendim yazmam zor olmazdi. 
X1_AMP, X2_AMP = np.max(np.abs(X1)), np.max(np.abs(X2))
X1_len, X2_len = X1.size, X2.size   
kernel = np.zeros(KERNEL_SIZE, dtype=np.float32)
kernel[0] = 1
for M in range(M_MIN, M_MAX + 1):
    for k in range(1, M + 1):
        kernel[GAP * k] = k * A
    
    myY1[M - 2] = myConv(X1, X1_len, kernel, KERNEL_SIZE) / X1_AMP
    Y1[M - 2] = np.convolve(X1, kernel) / X1_AMP
    myY2[M - 2] = myConv(X2, X2_len, kernel, KERNEL_SIZE) / X2_AMP
    Y2[M - 2] = np.convolve(X2, kernel) / X2_AMP


def play_rec(duration, data, rate, M=None, func_name=None):
    if func_name is None: 
        prompt = f"{duration} saniyelik kaydın seslendirmesi"
    else:
        prompt = f"{duration} saniyelik kayıt ve M = {M} için {func_name} seslendirmesi"
    print(prompt, end=" ")
    print("başladı")
    sd.play(data, rate)
    sd.wait()
    print(prompt, end=" ")
    print("bitti\n")


play_rec(SHORT_DUR, X1, RATE)
play_rec(LONG_DUR, X2, RATE)

for M in range(2, 5):
    signal_idx = M - 2
    play_rec(SHORT_DUR, myY1[signal_idx], RATE, M, "myConv")
    play_rec(SHORT_DUR, Y1[signal_idx], RATE, M, "numpy.convolve")
    play_rec(LONG_DUR, myY2[signal_idx], RATE, M, "myConv")
    play_rec(LONG_DUR, Y2[signal_idx], RATE, M, "numpy.convolve")

