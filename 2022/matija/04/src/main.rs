mod part1;
mod part2;

fn main() {
    let in_lines: Vec<String> = std::io::stdin().lines().collect::<Result<_, _>>().unwrap();

    println!(
        "Day 4: Camp Cleanup\nPart One: {}\nPart Two: {}",
        part1::solve(&in_lines),
        part2::solve(&in_lines)
    );
}
