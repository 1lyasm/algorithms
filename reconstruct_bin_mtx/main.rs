impl Solution {
    pub fn reconstruct_matrix(upper: i32, lower: i32, colsum: Vec<i32>) -> Vec<Vec<i32>> {
        let n_col = colsum.len() as i32;
        // println!("n_col: {}", n_col);
        let mut mtx = vec![vec![-1; n_col as usize]; 2];
        for i in 0..n_col {
            let cur_sum = colsum.get(i as usize).unwrap();
            if *cur_sum == 0 {
                *mtx.get_mut(0).unwrap().get_mut(i as usize).unwrap() = 0;
                *mtx.get_mut(1).unwrap().get_mut(i as usize).unwrap() = 0;
            } else if *cur_sum == 2 {
                *mtx.get_mut(0).unwrap().get_mut(i as usize).unwrap() = 1;
                *mtx.get_mut(1).unwrap().get_mut(i as usize).unwrap() = 1;
            }
        }
        let mut one_cnt = 0;
        for i in 0..n_col {
            let cur_item = mtx.get(0).unwrap().get(i as usize).unwrap();
            if *cur_item == 1 {
                one_cnt += *cur_item;
            }
        }
        println!("one_cnt: {}", one_cnt);
        let upper_remaining = upper - one_cnt;
        let mut no_sol = false;
        println!("upper_remaining: {}", upper_remaining);
        if upper_remaining < 0 {
            no_sol = true;
        }
        if !no_sol {
            let mut upper_filled = 0;
            for i in 0..n_col {
                let cur_item = mtx.get(0).unwrap().get(i as usize).unwrap();
                if *cur_item == -1 {
                    *mtx.get_mut(0).unwrap().get_mut(i as usize).unwrap() = 1;
                    upper_filled += 1;
                }
                if upper_filled == upper_remaining {
                    break;
                }
            }
            println!("upper_filled: {}", upper_filled);
        }
        let lower_remaining = lower - one_cnt;
        println!("lower_remaining: {}", lower_remaining);
        if lower_remaining < 0 {
            no_sol = true;
        }
        if !no_sol {
            let mut lower_filled = 0;
            for i in 0..n_col {
                let cur_upper = mtx.get(0).unwrap().get(i as usize).unwrap();
                let cur_lower = mtx.get(1).unwrap().get(i as usize).unwrap();
                if *cur_upper == -1 && *cur_lower == -1 {
                    *mtx.get_mut(1).unwrap().get_mut(i as usize).unwrap() = 1;
                    lower_filled += 1;
                }
                if lower_filled == lower_remaining {
                    break;
                }
            }
        }
        if !no_sol {
            for i in 0..2 {
                for j in 0..n_col {
                    let mut cell = mtx.get_mut(i as usize).unwrap().get_mut(j as usize).unwrap();
                    if cell == &(-1) {
                        *cell = 0;
                    }
                }
            }
        }
        if !no_sol {
            for i in 0..n_col {
                let cur_sum = colsum.get(i as usize).unwrap();
                if mtx.get(0).unwrap().get(i as usize).unwrap() +
                    mtx.get(1).unwrap().get(i as usize).unwrap() != *cur_sum {
                    no_sol = true;
                }
                if no_sol {
                    break;
                }
            }
        }
        if !no_sol {
            for i in 0..2 {
                let mut one_cnt = 0;
                for j in 0..n_col {
                    let cell = mtx.get(i as usize).unwrap().get(j as usize).unwrap();
                    if *cell == 1 {
                        one_cnt += 1;
                    }
                }
                if i == 0 {
                    if upper != one_cnt {
                        no_sol = true;
                    }
                }
                if i == 1 {
                    if lower != one_cnt {
                        no_sol = true;
                    }
                }
                if no_sol {
                    break;
                }
            }
            for i in 0..n_col {
                let mut one_cnt = 0;

            }
        }
        if no_sol {
           mtx = vec![];
        }
        return mtx;
    }
}
