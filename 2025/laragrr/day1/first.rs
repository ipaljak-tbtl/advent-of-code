use std::fs::read_to_string;
fn main() { 
   let mut position: i32 = 50;
   let mut count = 0;
   for line in read_to_string("input.txt").unwrap().lines() {
      let direction = &line[..1];
      let value: i32 = line[1..].parse::<i32>().unwrap() % 100;
      if direction == "L" {
         position = position - value;
         if position < 0 {
            position += 100;
         }
      }
      else if direction == "R" {
         position = position + value;
         if position > 99 {
            position -= 100;
         }
      }
      if position == 0 {
         count += 1;
      }
   }
   println!("{}", count);
}