/*2 64-digits numbers
a = 3141592653589793238462643383279502884197169399375105820974944592
b = 2718281828459045235360287471352662497757247093699959574966967627
*/
var a = 3141592653589793238462643383279502884197169399375105820974944592,
    b = 2718281828459045235360287471352662497757247093699959574966967627;
var multiplier = function (number1, number2){
    var digitOfNumber1 = Math.ceil(Math.log10(number1)),
    	digitOfNumber2 = Math.ceil(Math.log10(number2));
    if(digitOfNumber1 === 0)
    	return number1 * number2;
    var b = number1 % Math.pow(10, parseInt(digitOfNumber1 / 2)),
        a = (number1 - b) / Math.pow(10, parseInt(digitOfNumber1 / 2)),
    	d = number2 % Math.pow(10, parseInt(digitOfNumber2 / 2)),
        c = (number2 - d) / Math.pow(10, parseInt(digitOfNumber1 / 2));
    return Math.pow(10, digitOfNumber1) * multiplier(a, c) + Math.pow(10, digitOfNumber1 / 2) * (multiplier(a, d) + multiplier(b, c)) + multiplier(b, d);
};
console.log(multiplier(123, 456));