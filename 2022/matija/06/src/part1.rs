use itertools::Itertools as _;

pub fn solve(input: &str) -> usize {
    let n = 4;
    let mut queue = std::collections::VecDeque::new();

    for c in input.chars().take(n) {
        queue.push_front(c);
    }

    if queue.iter().unique().count() == n {
        return n;
    }

    for (i, c) in input.char_indices().skip(n) {
        queue.pop_back();
        queue.push_front(c);

        if queue.iter().unique().count() == n {
            return i + 1;
        }
    }

    0
}
