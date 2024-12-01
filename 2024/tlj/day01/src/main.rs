fn main() {
    // Read from file p1-in.txt into string
    let input = std::fs::read_to_string("in.txt").unwrap();

    let lines = input.split('\n').collect::<Vec<_>>();
    // Ignore last line because it's empty
    let lines = &lines[..lines.len() - 1];

    let (mut list1, mut list2) = lines
        .iter()
        .map(|l| {
            let splt = l.split("   ").collect::<Vec<_>>();
            (
                splt[0].parse::<i64>().unwrap(),
                splt[1].parse::<i64>().unwrap(),
            )
        })
        .collect::<(Vec<_>, Vec<_>)>();

    list1.sort();
    list2.sort();

    let mut dst = 0;

    for i in 0..list1.len() {
        dst += (list1[i] - list2[i]).abs();
    }

    let mut similarity = 0;
    for i in list1 {
        let count = list2.iter().filter(|x| **x == i).count() as i64;
        similarity += count * i;
    }

    println!("p1: {}", dst);
    println!("p2: {}", similarity);
}
