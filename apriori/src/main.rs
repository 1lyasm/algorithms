struct Itemset {
    item_list: Vec<String>
}

struct Itemsets {
    itemset_list: Vec<ItemSet>
}

struct Transactions {
    txn_list: Vec<Vec<&'static str>>,
}

impl Transactions {
    fn print(&self) {
        for t in &self.txn_list {
            for item in t {
                print!("{} ", item);
            }
            println!("");
        }
    }


    fn init_pass(&self) -> ItemSets {
        return ItemSets{item_set_list: };
    }

    fn apriori(&self) -> Rules {
        let candidates = self.init_pass();
        return Rules{rule_list: Vec::new()};
    }
}

struct Rule {
    left: Vec<String>,
    right: Vec<String>,
}

impl Rule {
    fn print_side(side: &Vec<String>) {
        for i in 0..side.len() {
            print!("{}", side.get(i).unwrap());
            if i != side.len() - 1 {
                print!(", ");
            }
        }
    }
}

struct Rules {
    rule_list: Vec<Rule>
}

impl Rules {
    fn print(&self) {
        for rule in &self.rule_list {
            Rule::print_side(&rule.left);
            print!("-> ");
            Rule::print_side(&rule.right);
            print!("\n");
        }
    }
}
fn main() {
    let txn_list = Transactions{txn_list: vec![vec!["a", "b"], vec!["c", "d"]]};
    txn_list.print();
    txn_list.apriori().print();
}

