use std::io::{self, Read};

#[derive(Clone, Copy, Debug, PartialEq)]
enum Block {
    Data(usize),
    Empty,
}

fn is_data_contiguous(chunks: &[Block]) -> (bool, u32) {
    let mut found_empty = false;

    let mut data_count = 0;
    for chunk in chunks {
        match chunk {
            Block::Data(_) => {
                if found_empty {
                    return (false, data_count);
                }
                data_count += 1;
            }
            Block::Empty => {
                found_empty = true;
            }
        }
    }

    (true, data_count)
}

fn find_last_id(chunks: &[Block]) -> usize {
    for chunk in chunks.iter().rev() {
        match chunk {
            Block::Data(i) => return *i,
            Block::Empty => continue,
        }
    }

    unreachable!();
}

fn find_last_contiguous(chunks: &[Block], id: usize) -> (usize, usize) {
    let end = chunks.iter().rposition(|b| *b == Block::Data(id)).unwrap();
    let mut start = end as i64;

    while start > 0 && chunks[start as usize] == Block::Data(id) {
        start -= 1;
    }

    ((start + 1) as usize, end)
}

fn find_first_empty(chunks: &[Block]) -> (usize, usize) {
    let start = chunks.iter().position(|b| matches!(b, Block::Empty));

    let Some(start) = start else {
        return (chunks.len(), chunks.len());
    };

    let mut end = start;

    while end < chunks.len() && chunks[end] == Block::Empty {
        end += 1;
    }

    (start, end)
}

fn main() {
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    let mut line = String::new();
    handle.read_to_string(&mut line).unwrap();

    let nums = line
        .chars()
        .filter_map(|c| c.to_digit(10))
        .collect::<Vec<_>>();

    let mut blocks = Vec::<Block>::new();

    for (i, num) in nums.iter().enumerate() {
        for _ in 0..*num {
            if i % 2 == 0 {
                blocks.push(Block::Data(i / 2));
            } else {
                blocks.push(Block::Empty);
            }
        }
    }

    let mut blocks2 = blocks.clone();

    let mut contiguous_count = 0;
    loop {
        let cont = is_data_contiguous(&blocks[contiguous_count..]);

        if cont.0 {
            break;
        }

        contiguous_count = cont.1 as usize;

        let first_empty = blocks[contiguous_count..]
            .iter()
            .position(|b| matches!(b, Block::Empty))
            .unwrap();

        let last_data = blocks[contiguous_count..]
            .iter()
            .rposition(|b| matches!(b, Block::Data(_)))
            .unwrap();

        blocks.swap(contiguous_count + first_empty, contiguous_count + last_data);
    }

    let checksum = blocks
        .iter()
        .enumerate()
        .filter_map(|(idx, b)| match b {
            Block::Data(i) => Some(i * idx),
            Block::Empty => None,
        })
        .sum::<usize>();

    println!("p1: {}", checksum);

    let mut idx: i64 = find_last_id(&blocks2) as i64;
    loop {
        if idx == -1 {
            break;
        }

        let (start, end) = find_last_contiguous(&blocks2, idx as usize);
        idx -= 1;

        let mut empty_start = 0;
        loop {
            let (first_empty_start, first_empty_end) = find_first_empty(&blocks2[empty_start..]);

            if first_empty_start + empty_start > end {
                break;
            }

            if first_empty_end - first_empty_start >= end - start + 1 {
                for i in 0..(end - start + 1) {
                    blocks2.swap(first_empty_start + empty_start + i, start + i);
                }

                break;
            }

            empty_start += first_empty_end;
        }
    }

    let checksum2 = blocks2
        .iter()
        .enumerate()
        .filter_map(|(idx, b)| match b {
            Block::Data(i) => Some(i * idx),
            Block::Empty => None,
        })
        .sum::<usize>();

    println!("p2: {}", checksum2);
}
