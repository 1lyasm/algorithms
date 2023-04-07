import numpy as np
import numpy.fft as fft
import matplotlib.pyplot as plt
import soundfile as sf
from termcolor import colored
import math as math

class Plotter:
    T_SIGS = []
    SIG_NAMES = []

    F_SIGS = []
    F_INFO = []

    @staticmethod
    def __plot_cont(axis, sig, sig_nm, has_y_lbl):
        XLBL, YLBL = "Time t (sec)", "Amplitude x(t)"
        t = np.arange(0, len(sig))
        axis.plot(t, sig)
        axis.set_title(f'{sig_nm} sinyali')
        axis.set_xlabel(XLBL)
        if has_y_lbl:
            axis.set_ylabel(YLBL)

    @staticmethod
    def __plot_discrete(axis, sig, sig_nm, has_y_lbl):
        SPACING = 4
        XLBL, YLBL = "Sample n", "Amplitude x[n]"
        sampled_sig = sample_sig(sig, SPACING)
        n = np.arange(0, len(sampled_sig))
        axis.stem(n, sampled_sig, linefmt="k-", basefmt=" ")
        axis.set_xlabel(XLBL)
        if has_y_lbl:
            axis.set_ylabel(YLBL)

    @staticmethod
    def __plot_t_sig():
        SIG_CNT = 2
        if len(Plotter.T_SIGS) != SIG_CNT:
            raise ValueError("Only two signals can be plotted in time domain")
        FIGSIZE = (19, 10)
        PLOT_LBL = "t-domain plots"
        NROWS, NCOLS = 2, SIG_CNT
        fig, axes = plt.subplots(nrows=NROWS, ncols=NCOLS, figsize=FIGSIZE, num=PLOT_LBL)
        for i, sig in enumerate(Plotter.T_SIGS):
            sig_nm = Plotter.SIG_NAMES[i]
            has_y_lbl = False
            if i == 0:
                has_y_lbl = True
            Plotter.__plot_cont(axes[0][i], sig, sig_nm, has_y_lbl)
            Plotter.__plot_discrete(axes[1][i], sig, sig_nm, has_y_lbl)

    @staticmethod
    def __plot_f_sig():
        SIG_CNT = 2
        SIG_0_LEN = len(Plotter.F_SIGS[0])
        if len(Plotter.F_SIGS) != SIG_CNT:
            raise ValueError("Only two signals can be plotted in frequency domain")
        if SIG_0_LEN != len(Plotter.F_SIGS[1]):
            raise ValueError("Two numbers must have same size for comparison")
        FIGSIZE = (19, 10)
        PLOT_LBL = "f-domain plots"
        NROWS, NCOLS = SIG_CNT, SIG_0_LEN
        fig, axes = plt.subplots(nrows=NROWS, ncols=NCOLS, figsize=FIGSIZE, num=PLOT_LBL)
        for i, sig in enumerate(Plotter.F_SIGS):
            for j, time_block in enumerate(sig):
                axes[i][j].plot(time_block[0], time_block[1])
                axes[i][j].set_title(
                    f"{Plotter.F_INFO[i][0][j]}: [{str(int(Plotter.F_INFO[i][1][j][0]))}, {str(int(Plotter.F_INFO[i][1][j][1]))}]")
                if j != 0:
                    axes[i][j].tick_params(axis='y', which='both', labelleft=False)
                if i != SIG_CNT - 1:
                    axes[i][j].tick_params(axis='x', which='both', labelbottom=False)
        LBL_XPOS, UP_LBL_YPOS, LBL_Y_SEP = 0.015, 0.9, 0.425
        for i in range(SIG_CNT):
            axes[i][0].annotate(Plotter.SIG_NAMES[i].replace(".wav", ""),
                xy=(LBL_XPOS, UP_LBL_YPOS - i * LBL_Y_SEP),
                xycoords='figure fraction', fontweight="extra bold",
                fontsize="xx-large")

    @staticmethod
    def plot():
        Plotter.__plot_t_sig()
        Plotter.__plot_f_sig()
        plt.show()


class FreqTable:
    ROW_FREQ_ARR = np.array([697, 770, 852, 941])
    COL_FREQ_ARR = np.array([1209, 1336, 1477])
    KEYS_DICT = {0: "1", 1: "2", 2: "3", 3: "4", 4: "5", 5: "6",
        6: "7", 7: "8", 8: "9", 9: "*", 10: "0", 11: "#"}

    @staticmethod
    def __keys_to_idx_arr(keys_str, str_len):
        key_idx_arr = np.zeros(str_len)
        key_idx  = 0
        for (i, key) in enumerate(keys_str):
            if (key == "*"): key_idx = 9
            elif (key == "0"): key_idx = 10
            elif (key == "#"): key_idx = 11
            else: key_idx = int(key) - 1
            key_idx_arr[i] = key_idx
        return key_idx_arr

    @staticmethod
    def keys_to_freq_mtx(keys_str):
        STR_LEN = len(keys_str)
        KEY_IDX_ARR =  FreqTable.__keys_to_idx_arr(keys_str, STR_LEN)
        freq_mtx  = np.array([(0, 0) for i in range(STR_LEN)])
        row_idx, col_idx = 0, 0
        for (i, key_idx) in enumerate(KEY_IDX_ARR):
            row_idx = int(np.floor(key_idx / 3))
            col_idx = int(key_idx % 3)
            freq_mtx[i] = (FreqTable.ROW_FREQ_ARR[row_idx], FreqTable.COL_FREQ_ARR[col_idx])
        return freq_mtx

    @staticmethod
    def freq_mtx_to_keys(freq_mtx):
        keys_str = ""
        for freq_pair in freq_mtx:
            keys_str += FreqTable.KEYS_DICT[
                np.argmin(np.abs(FreqTable.ROW_FREQ_ARR - freq_pair[0])) * 3 + \
                np.argmin(np.abs(FreqTable.COL_FREQ_ARR - freq_pair[1]))]
        return keys_str

    
def synthesize(freq_arr = None, rate = None, dur = None, amplitude=None):
    SAMPLE_LEN = round(rate * dur)
    COMMON_CONST = np.arange(0, SAMPLE_LEN) * 2 * np.pi / rate
    return amplitude * (np.cos(COMMON_CONST * freq_arr[0]) + \
        np.cos(COMMON_CONST * freq_arr[1]))


def record_ph_num(ph_num):
    S_RATE = 8000
    DUR_KEY_SND = np.float_(0.2)
    GAP_RATIO = np.float_(0.4)
    AMPLITUDE = 0.5
    FILE_NM = "OgrenciTelefoNo.wav"
    LEN_PH_NUM = len(ph_num)
    LEN_KEY_SND = round(S_RATE * DUR_KEY_SND)
    DUR_PRESS = np.float_(DUR_KEY_SND * (1 - GAP_RATIO))
    LEN_PRESS = round(S_RATE * DUR_PRESS)
    LEN_TOT_SND = LEN_KEY_SND * LEN_PH_NUM
    FREQ_MTX = FreqTable.keys_to_freq_mtx(ph_num)
    snd_wave = np.zeros(LEN_TOT_SND)
    for i in range(LEN_PH_NUM):
        snd_wave[int(i * LEN_KEY_SND):int(i * LEN_KEY_SND + LEN_PRESS)] = \
            synthesize(freq_arr=FREQ_MTX[i], rate=S_RATE, dur=DUR_PRESS, amplitude=AMPLITUDE)
    sf.write(FILE_NM, snd_wave, S_RATE)
    print(f"wrote sound of my phone number to {FILE_NM}", end="")
    return FILE_NM


def extract_freqs(freqs, amps, len_amps):
    THRESHOLD = max(amps) * 0.7
    N_BINS = 100
    BIN_WID = round(len_amps / N_BINS)
    extracted = np.array([])
    bin_st = -BIN_WID
    bin_end = 0
    for i in range(len_amps):
        bin_st += BIN_WID
        bin_end = bin_st + BIN_WID
        if bin_end > len_amps:
            bin_end = len_amps
        if (bin_st < bin_end):
            bin_max = max(amps[bin_st:bin_end])
        else: continue  
        max_idx = bin_st + amps[bin_st:bin_end].tolist().index(bin_max)
        if bin_max > THRESHOLD:
            freq = freqs[max_idx]
            if (freq > 0):
                extracted = np.append(extracted, round(freq))
            if extracted.size > 2:
                raise ValueError("Maximum number of frequencies is 2")
    return extracted


def find_gap_bounds(sig):
    MIN_GAP_WID = 3
    LEN_SIG = len(sig)
    gap_bounds = np.empty(0, dtype=int)
    idx = 0
    while idx < LEN_SIG:
        val = sig[idx]
        if val == 0:
            l_bnd = idx
            zero_cnt = 0
            idx += 1
            while val == 0 and (idx < len(sig)):
                zero_cnt += 1
                val = sig[idx]
                idx += 1
            r_bnd = idx - 2
            if zero_cnt >= MIN_GAP_WID:
                gap_bounds = np.append(gap_bounds, [l_bnd, r_bnd])
        idx += 1
    gap_bounds = np.append((np.insert(gap_bounds, 0, 0)), LEN_SIG - 1)
    return gap_bounds


def sample_sig(sig, spacing):
    return sig[np.array([int(spacing * i)
        for i in range(math.ceil(len(sig) / spacing))], dtype=int)]


def analyze_wav(f_nm):
    snd_wave, S_RATE = sf.read(f_nm)
    Plotter.T_SIGS.append(snd_wave)
    Plotter.F_SIGS.append([])
    Plotter.F_INFO.append([])
    Plotter.SIG_NAMES.append(f_nm)
    S_SPACING = 1 / S_RATE
    LEN_TOT_SND = len(snd_wave)
    N_FREQ = 2
    MIN_LEN_AMPS = 100
    freq_mtx = np.empty(0)
    gap_bounds = find_gap_bounds(snd_wave)
    i = 0
    while i < len(gap_bounds) - 1:
        l_bnd, r_bnd = gap_bounds[i], gap_bounds[i + 1]
        amps = np.abs(fft.fft(snd_wave[l_bnd:r_bnd]))
        LEN_AMPS = amps.size
        freqs = fft.fftfreq(LEN_AMPS, S_SPACING)
        if LEN_AMPS > MIN_LEN_AMPS:
            Plotter.F_SIGS[-1].append((freqs, amps))
        freq_mtx = np.append(freq_mtx, extract_freqs(freqs, amps, LEN_AMPS))
        i = i + 2
    freq_mtx = freq_mtx.reshape((-1, 2))
    keys = FreqTable.freq_mtx_to_keys(freq_mtx)
    print(f"number dialed in {f_nm}: ", keys, end="")
    Plotter.F_INFO[-1].append(keys)
    Plotter.F_INFO[-1].append(freq_mtx)
    return None


def print_delim():
    WID = 50
    for i in range(WID):
        print("-", end="")


def print_q_lbl(n_question, with_delim=True):
    LBL_COLOR = "green"
    print("\n")
    if with_delim is True:
        print_delim(), print("\n")
    print(colored(f"Soru {n_question}", LBL_COLOR), "\n")


def main() -> None:
    PH_NUM  = "05528189351"
    question_no = 1
    print_q_lbl(question_no, with_delim=False)
    MY_F_NM = record_ph_num(PH_NUM)
    question_no += 1
    print_q_lbl(question_no)
    analyze_wav(MY_F_NM)
    question_no += 1
    print_q_lbl(question_no)
    EX_F_NM = "Ornek.wav"
    analyze_wav(EX_F_NM)
    print(" (phone number of ceng department, code is verified :) )")
    question_no += 1
    Plotter.plot()
    # print(len(Plotter.F_SIGS))
    # print(len(Plotter.F_SIGS[-1]))
    # print(len(Plotter.F_SIGS[-1][-1]))
    # print(len(Plotter.F_SIGS[-1][-1][-1]))


if __name__ == "__main__":
    main()