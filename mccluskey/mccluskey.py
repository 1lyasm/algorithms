F = "A'BC'D' + AB'C'D' + AB'CD' + AB'CD + ABC'D' + ABCD + AB'C'D + ABCD'"


def make_binary(F):
    splitted_F = F.split(" + ")
    minterm_lst = []
    for minterm in splitted_F:
        minterm_lst.append("")

        i = 0
        len_minterm = len(minterm)
        while i <= len_minterm - 1:
            if (i <= len_minterm - 2) \
                and (minterm[i + 1] == "'"):
                minterm_lst[-1] = minterm_lst[-1] + "0"
                i = i + 1
            else:
                minterm_lst[-1] = minterm_lst[-1] + "1"
            i = i + 1
    return minterm_lst


def group_minterms(F):
    binary_minterms = make_binary(F)
    var_amt = len(binary_minterms[0])
    minterm_group = [[] for i in range(var_amt)]
    for minterm in binary_minterms:
        one_count = minterm.count("1") 
        minterm_group[one_count - 1].append(minterm)
    return minterm_group

def get_neighbors(minterm, var_amt):
    neighbor_lst = []
    for i in range(var_amt):
        neighbor = minterm
        neighbor = list(neighbor)
        if neighbor[i] == "1":
            neighbor[i] = "0"
        elif neighbor[i] == "0":
            neighbor[i] = "1"
        neighbor = "".join(neighbor)
        if neighbor != minterm:
            neighbor_lst.append(neighbor)
    return neighbor_lst


def remove_dup(groups_lst):
    singular_lst = []
    for group in groups_lst:
        singular_lst.append(group)

        j = len(singular_lst) - 2
        found = False
        while (j >= 0) and (not found):
            if group == singular_lst[j]:
                singular_lst.pop()
                found = True
            j = j - 1
    return singular_lst


def merge_minterms(group):
    merged = [""]
    for bit1, bit2 in zip(group[0], group[1]):
        if bit1 != bit2:
            merged[0] = merged[0] + "_"
        else:
            merged[0] = merged[0] + bit1
    return merged


def make_groups(previous_minterms, final_implicants, var_amt):
    groups_lst = []
    for minterm in previous_minterms:
        neighbor_lst = get_neighbors(minterm, var_amt)
        for neighbor in neighbor_lst:
            i = 0
            found = False
            while (i <= len(previous_minterms) - 1) and (not found):
                other_minterm = previous_minterms[i]
                if neighbor == other_minterm:
                    groups_lst.append(sorted([neighbor, minterm]))
                    found = True
                i = i + 1
        if (len(groups_lst) < 1) or minterm not in groups_lst[-1]:
            final_implicants.append(minterm)

    return remove_dup(groups_lst)


def flatten(groups):
    flat = []
    for group in groups:
        for elem in group:
            flat.append(elem)
    return flat


def expand(implicant):
    expanded_lst = [implicant]
    i = 0
    while i <= len(expanded_lst) - 1:
        term = expanded_lst[i]
        expanded_once = False
        j = 0
        while (j <= len(term) - 1) and (not expanded_once):
            if term[j] == "_":
                expanded_lst.pop(i)
                bit_lst = list(term)
                expanded = bit_lst
                expanded[j] = "0"
                expanded_lst.append("".join(expanded))
                expanded[j] = "1"
                expanded_lst.append("".join(expanded))
                i = -1
                expanded_once = True
            j = j + 1
        i = i + 1
    return expanded_lst
    

def all_true(bool_arr):
    for bit in bool_arr:
        if bit is False:
            return False
    return True


def permute(nums):
    result = []

    if (len(nums) == 1):
        return [nums[:]]

    for i in range(len(nums)):
        n = nums.pop(0)
        perms = permute(nums)

        for perm in perms:
            perm.append(n)
        
        result.extend(perms)
        nums.append(n)

    return result
    

def find_essential_implicants(minterms, implicants, var_amt):
    covered_lst = [False for i in range(len(minterms))]
    permutation_lst = permute([i for i in range(var_amt)])
    implicant_coverage_lst = []
    for j in range(len(permutation_lst)):
        implicant_coverage_lst.append([])
        for implicant_idx in permutation_lst[j]:
            implicant = implicants[implicant_idx]
            expanded_implicant = expand(implicant)
            implicant_coverage_lst[-1].append(implicant)
            i = 0
            while (i <= len(minterms) - 1) and (not all_true(covered_lst)):
                minterm = minterms[i]
                is_covered = covered_lst[i]
                if not is_covered:
                    if minterm in expanded_implicant:
                        covered_lst[i] = True
                i = i + 1
    coverage_len_lst = []
    for implicant_coverage in implicant_coverage_lst:
        coverage_len_lst.append(len(implicant_coverage))

    i = 0
    min_idx = 0
    min_ = coverage_len_lst[i]
    while (i <= len(coverage_len_lst) - 1):
        if coverage_len_lst[i] < min_:
            min_ = coverage_len_lst[i]
            min_idx = i
        i = i + 1
    essential_implicants = implicant_coverage_lst[min_idx]
    return essential_implicants


def quine_simplify(F):
    minterms = make_binary(F)
    var_amt = len(minterms[0])
    final_implicants = []

    there_is_new_group = True
    previous_minterms = minterms
    while there_is_new_group:
        groups_lst = make_groups(previous_minterms, final_implicants, var_amt)
        if len(groups_lst) < 1:
            there_is_new_group = False
        
        for i in range(len(groups_lst)):
            groups_lst[i] = merge_minterms(groups_lst[i])
        groups_lst = remove_dup(groups_lst)
        
        previous_minterms = flatten(groups_lst)

    essential_implicants = find_essential_implicants(minterms, final_implicants, var_amt)
    return essential_implicants


simple_F = quine_simplify(F)

print(simple_F)

