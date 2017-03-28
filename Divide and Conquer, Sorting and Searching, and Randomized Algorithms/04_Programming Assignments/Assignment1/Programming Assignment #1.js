/*2 64-digits numbers multiplication
a = 3141592653589793238462643383279502884197169399375105820974944592
b = 2718281828459045235360287471352662497757247093699959574966967627
*/
var x = "3141592653589793238462643383279502884197169399375105820974944592",
    y = "2718281828459045235360287471352662497757247093699959574966967627";

String.prototype.splice = function (idx, rem, str) {
		return this.slice(0, idx) + str + this.slice(idx + Math.abs(rem));
};

var split = function (number) {
	return [number.slice(0, number.length / 2), number.slice(number.length / 2, number.length)];
}

var singleDigitMultiplier = function (number1, number2){
	var multi = number1 * number2;
	return multi.toString();
}

var singleDigitAdder = function (number1, number2) {
	var result = Number(number1) + Number(number2);
	return result.toString();
}

var multiDigitAdder = function (number1, number2) {
	var result = "", temp = "", carry = "0", carryAll = 0;
	var numDigitsNumber1 = number1.length, numDigitsNumber2 = number2.length;
	if(numDigitsNumber1 < numDigitsNumber2){
		for(var i = 0; i < numDigitsNumber2 - numDigitsNumber1; i++)
			number1 = number1.splice(0, 0, "0");
	}
	else if(numDigitsNumber2 < numDigitsNumber1){
		for(var i = 0; i < numDigitsNumber1 - numDigitsNumber2; i++)
			number2 = number2.splice(0, 0, "0");
	}
	for(var i = 0; i < number1.length; i++)
		result += "0";
	for(i = number1.length - 1; i > -1; i--){
		temp = singleDigitAdder(number1[i], number2[i]);
		if(temp.length > 1){
			carry = "1";
			result = result.splice(i, 1, temp[1]);
			if(i === 0)
				carryAll = 1;
			for(var j = i - 1; j > -1; j--){
				if(number1[j] === "9"){
					number1 = number1.splice(j, 1, "0");
					if(j === 0)
						carryAll = 1;
				}
				else{
					number1 = number1.splice(j, 1, singleDigitAdder(carry, number1[j]));
					carry = "0";
					break;
				}
			}
		}
		else
			result = result.splice(i, 1, temp);
	}
	if(carryAll)
		result = result.splice(0, 0, "1");
	return result;
}

var multiplier = function (number1, number2) {
	var result = "", temp1 = [], temp2 = [], numDigits1 = number1.length, numDigits2 = number2.length;
	var power = "", halfPower = "";
	var a, b, c, d;
	for(var i = 0; i < numDigits1; i++)
		power += "0";
	for(var i = 0; i < numDigits1 / 2; i++)
		halfPower += "0";
	if(numDigits1 === 1 || numDigits2 === 1){
		return singleDigitMultiplier(number1, number2);
	}
	else{
		temp1 = split(number1);
		temp2 = split(number2);
		a = multiplier(temp1[0], temp2[0]) + power;
		b = multiplier(temp1[1], temp2[0]);
		c = multiplier(temp1[0], temp2[1]);
		d = multiplier(temp1[1], temp2[1]);
		return multiDigitAdder(multiDigitAdder(a, d), multiDigitAdder(b, c) + halfPower);
	}
}

console.log(multiplier(x, y));