#[derive(Debug)]
enum Packet {
    List(Vec<Packet>),
    Integer(u32),
}

fn compare(p1: &Packet, p2: &Packet) -> i8 {
    match (p1, p2) {
        (Packet::Integer(i1), Packet::Integer(i2)) => match i1.cmp(i2) {
            std::cmp::Ordering::Less => -1,
            std::cmp::Ordering::Greater => 1,
            std::cmp::Ordering::Equal => 0,
        },
        (Packet::List(_), Packet::Integer(i2)) => {
            compare(p1, &Packet::List(vec![Packet::Integer(*i2)]))
        }
        (Packet::Integer(i1), Packet::List(_)) => {
            compare(&Packet::List(vec![Packet::Integer(*i1)]), p2)
        }
        (Packet::List(l1), Packet::List(l2)) => {
            let mut order = 0;

            for (e1, e2) in l1.iter().zip(l2) {
                let cmp = compare(e1, e2);
                if cmp != 0 {
                    order = cmp;
                    break;
                }
            }

            if order == 0 {
                order = match l1.len().cmp(&l2.len()) {
                    std::cmp::Ordering::Less => -1,
                    std::cmp::Ordering::Greater => 1,
                    std::cmp::Ordering::Equal => 0,
                }
            }

            order
        }
    }
}

impl Packet {
    fn from_str(packet: &str) -> Self {
        Self::new(&packet.chars().collect::<Vec<char>>())
    }

    fn new(packet: &[char]) -> Self {
        let mut packets: Vec<Self> = Vec::new();

        let mut i = 1;
        while i + 1 < packet.len() {
            if packet[i].is_ascii_digit() {
                let mut n = String::new();

                while packet[i].is_ascii_digit() {
                    n.push(packet[i]);
                    i += 1;
                }

                packets.push(Self::Integer(n.parse().unwrap()));
                i += 1;
            } else {
                let start_i = i;
                let mut cnt_bracket = 1;

                while cnt_bracket != 0 {
                    i += 1;

                    if packet[i] == '[' {
                        cnt_bracket += 1;
                    } else if packet[i] == ']' {
                        cnt_bracket -= 1;
                    }
                }

                packets.push(Self::new(&packet[start_i..(i + 1)]));
                i += 2;
            }
        }

        Self::List(packets)
    }
}

pub fn solve(input: &[String]) -> usize {
    let d1 = Packet::from_str("[[2]]");
    let d2 = Packet::from_str("[[6]]");

    let mut d1i = 1;
    let mut d2i = 2;

    let mut i = 0;
    while i + 1 < input.len() {
        let p1 = Packet::from_str(&input[i]);
        let p2 = Packet::from_str(&input[i + 1]);

        if compare(&p1, &d1) == -1 {
            d1i += 1;
        }

        if compare(&p1, &d2) == -1 {
            d2i += 1;
        }

        if compare(&p2, &d1) == -1 {
            d1i += 1;
        }

        if compare(&p2, &d2) == -1 {
            d2i += 1;
        }

        i += 3;
    }

    d1i * d2i
}
