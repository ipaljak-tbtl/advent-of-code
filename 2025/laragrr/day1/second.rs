use std::fs::read_to_string;

fn main() {
   let mut position: i32 = 50;
   let mut count: i32 = 0;

   let contents = read_to_string("input.txt").expect("failed to read input.txt");
   for raw_line in contents.lines() {
      let line = raw_line.trim();
      if line.is_empty() { continue; }

      let dir = line.chars().next().unwrap();
      let value: i32 = line[1..].trim().parse().unwrap();

      let full = value.div_euclid(100);
      let rem  = value.rem_euclid(100);
      count += full;

      println!("position: {}, line: {}", position, line);
      if dir == 'R' {
         let raw_pos = position + rem;
         if raw_pos > 99 {
               position = raw_pos - 100;
               count += 1;
         } else {
               position = raw_pos;
         }
      } else if dir == 'L' {
         let raw_pos = position - rem;
         if raw_pos < 0 {
               position = raw_pos + 100;
               if position != 0 {
                     count += 1;
               }
         } else {
               position = raw_pos;
         }
      } else {
         panic!("unknown direction: {}", dir);
      }
      println!("new count: {}", count);
   }
   println!("{}", count);
}