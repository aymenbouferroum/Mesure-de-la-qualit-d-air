// Decode uplink messages (buffer of bytes to an object of integers )
function decodeUplink(input) {
var data = {}; // Define an object to store measurements
// Hexadecimal to decimal
var t = input.bytes[0] * 256 + input.bytes[1];
var h = input.bytes[2] * 256 + input.bytes[3];
var c = input.bytes[4] * 256 + input.bytes[5];
var tvoc = input.bytes[6] * 256 + input.bytes[7];

// Divide by 100 to get the full measure (example : 2250 ==> 22,5)
data.temperature = t/100;
data.humidity = h/100;
data.co2 = c/100;
data.tvoc = tvoc/100;
return {
  data:   data,
  warnings: [],
  errors: []
};
}
