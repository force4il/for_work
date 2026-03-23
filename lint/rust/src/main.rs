use std::io; 

fn mult_or_add(data: &(i16, i16)) -> i16
{
	if data.0 > data.1 {return data.0 + data.1;}
	else {return data.0 * data.1;}
}

fn new_arr(arr: &(i16, i16), new_arr: &mut Vec<i16>)
{
    new_arr.push(arr.0 + arr.1);
    new_arr.push(arr.0 - arr.1);
    new_arr.push(arr.0 * arr.1);
    new_arr.push(arr.0 / arr.1);
}

fn main()
{
	let mut num1 = String::new();
	let mut num2 = String::new();

	println!("Enter num1: ");
	io::stdin().read_line(&mut num1).expect("Fail input for num1");
	println!("Enter num2: ");
	io::stdin().read_line(&mut num2).expect("Fail input for num2");

	let data1: i16 = num1.trim().parse().expect("not number");
	let data2: i16 = num2.trim().parse().expect("not number");

	println!("res 1: {}, res 2: {}", data1, data2);

	let res = data1 + data2;
	println!("res: {}", res);

	let arr = (data1, data2);
	println!("After func: {}", mult_or_add(&arr));

    let mut second_arr = Vec::new();
    new_arr(&arr, &mut second_arr);
    println!("{:?}", second_arr);
}