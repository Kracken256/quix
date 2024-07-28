#include <quix-lexer/Lib.h>

#include <chrono>
#include <filesystem>
#include <iostream>
#include <string_view>
#include <unordered_map>
#include <vector>

struct Dist {
  std::unordered_map<qlex_ty_t, size_t> counts;
};

void do_dist(FILE *file) {
  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  fseek(file, 0, SEEK_SET);

  size_t tok_count = 0;
  Dist dist;

  {
    qlex_t *lexer = qlex_new(file);

    qlex_tok_t tok;
    while ((tok = qlex_next(lexer)).ty != qEofF) {
      ++dist.counts[tok.ty];
      ++tok_count;
    }

    qlex_free(lexer);
  }

  std::cout << "Token distribution:" << std::endl;
  std::vector<std::pair<qlex_ty_t, size_t>> sorted;
  for (const auto &[ty, count] : dist.counts) {
    sorted.push_back({ty, count});
  }
  std::sort(sorted.begin(), sorted.end(),
            [](const auto &a, const auto &b) { return a.second > b.second; });
  for (const auto &[ty, count] : sorted) {
    std::cout << "  " << qlex_ty_str(ty) << ": " << count << std::endl;
  }
}

int main(int argc, char **argv) {
  qlex_lib_init();

  std::vector<std::string_view> args(argv, argv + argc);

  if (args.size() < 2) {
    std::cerr << "Usage: " << args[0] << " <input-file>" << std::endl;
    return 1;
  }

  if (!std::filesystem::exists(args[1])) {
    std::cerr << "File not found: " << args[1] << std::endl;
    return 1;
  }

  FILE *file = fopen(args[1].data(), "r");
  if (!file) {
    std::cerr << "Failed to open file: " << args[1] << std::endl;
    return 1;
  }

  do_dist(file);

  fclose(file);

  qlex_lib_deinit();
}