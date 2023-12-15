fn hash(input: &str) -> u32 {
    input
        .chars()
        .fold(0, |acc, c| ((acc + c as u32) * 17) % 256)
}

fn solve(reader: impl std::io::BufRead) -> u32 {
    let line = reader.lines().next().unwrap().unwrap();
    line.split(',').map(hash).sum()
}

fn main() {
    println!("{}", solve(std::io::stdin().lock()));
}
