#include <bits/stdc++.h>

class Candidate {
public:
  long unsigned int wgt = 0;
  long double prob = 0;

public:
  Candidate(int wgt, long double prob) : wgt(wgt), prob(prob) {}
  void print() {
    std::cout << "Candidate: ("
              << "wgt(" << this->wgt << "), "
              << "prob(" << this->prob << ") )\n";
  }
};

class Round {
public:
  std::list<std::list<Candidate>> players;

public:
  void print(void) {
    std::cout << "Round {\n";
    int node_cntr = 0;
    for (auto node : this->players) {
      int cand_cntr = 0;
      std::cout << "    Node " << node_cntr << " [\n";
      for (auto cand : node) {
        std::cout << "        ";
        cand.print();
        ++cand_cntr;
      }
      ++node_cntr;
      std::cout << "    ]\n";
    }
    std::cout << "}\n";
    return;
  }

  void push_player(std::list<Candidate> cand_list) {
    this->players.push_back(cand_list);
  }

  void push_cand(Candidate cand) { this->players.back().push_back(cand); }
};

template <typename T> void print_vec(T val) {
  for (size_t i = 0; i <= val.size() - 1; i++) {
    std::cout << val[i];
    if (i != val.size() - 1) {
      std::cout << ' ';
    }
  }
  return;
}

std::deque<std::deque<unsigned int>> compute_rk(unsigned int r0) {
  std::deque<unsigned int> r, k;
  int r_new = r0, r_last, k_last;
  r.push_back(r_new);
  while (r_new != 1) {
    r_last = r[r.size() - 1];
    k_last = 2 * (r_last - (int)pow(2, (int)(floor(log2(r_last - 1)))));
    r_new = r_last - (int)(k_last / 2);
    k.push_back(k_last);
    r.push_back(r_new);
  }
  std::deque<std::deque<unsigned int>> rk;
  rk.push_back(r);
  rk.push_back(k);
  return rk;
}

void make_players(Round &r0, unsigned int nplayer,
                  std::list<long unsigned int> wgt_lst) {
  Candidate cand(0, 1);
  std::list<Candidate> cand_list = {cand};
  for (auto wgt : wgt_lst) {
    cand.wgt = wgt;
    cand_list.pop_front();
    cand_list.push_front(cand);
    r0.push_player(cand_list);
  }
}

void compete(std::list<Candidate> node1, std::list<Candidate> node2,
             Round &round) {
  long double posterior_prob;
  for (auto cand1 : node1) {
    posterior_prob = 0;
    long unsigned int cand1_wgt = cand1.wgt;
    for (auto cand2 : node2) {
      posterior_prob += cand2.prob / (cand1_wgt + cand2.wgt);
    }
    round.push_cand(
        Candidate(cand1_wgt, posterior_prob * cand1.prob * cand1_wgt));
    return;
  }
}

std::list<Candidate> forward(Round &round, std::deque<unsigned int> k) {
  std::list<Candidate> pl_1, pl_2, empty_node;
  int n_pushed_back;
  // DELETE
  round.print();

  for (int i = 0; i < static_cast<int>(k.size()); i++) {
    n_pushed_back = 0;
    for (unsigned int j = 0; 2 * j + 2 <= k[i]; ++j) {
      pl_1 = round.players.front();
      round.players.pop_front();
      pl_2 = round.players.front();
      round.players.pop_front();
      round.players.push_back(empty_node);
      compete(pl_1, pl_2, round);
      compete(pl_2, pl_1, round);
      ++n_pushed_back;
    }

    for (int i = 0; i < n_pushed_back; ++i) {
      round.players.push_front(round.players.back());
      round.players.pop_back();
    }

    // DELETE
    round.print();
  }
  return round.players.front();
}

void print_node_probs(std::list<Candidate> node) {
  std::cout << std::fixed;
  std::cout << std::setprecision(10);
  for (auto cand : node) {
    std::cout << cand.prob << " ";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  unsigned int nplayer;
  std::cin >> nplayer;
  std::list<long unsigned int> wgt_lst;

  if (nplayer == 1) {
    std::cin >> nplayer;
    std::ifstream infile;
    infile.open("random_ints.txt");
    long unsigned int temp_wgt;
    for (unsigned int i = 0; i < nplayer; i++) {
      infile >> temp_wgt;
      wgt_lst.push_back(temp_wgt);
    }
    infile.close();
  } else {
    long unsigned int temp_wgt;
    for (unsigned int i = 0; i < nplayer; i++) {
      std::cin >> temp_wgt;
      wgt_lst.push_back(temp_wgt);
    }
  }
  std::deque<std::deque<unsigned int>> rk = compute_rk(nplayer);
  std::deque<unsigned int> k(rk[1]);

  Round r0;
  make_players(r0, nplayer, wgt_lst);

  std::list<Candidate> cand_lst = forward(r0, k);

  print_node_probs(cand_lst);

  return 0;
}
