
const TelegramBot = require('node-telegram-bot-api');
var mqtt = require('mqtt')
const token = '1093970624:AAGv5-k6E53uApfVZYPwalgcE73Z5E14Ud8';
//const token = '1093970624:AAGv5-k6E53uApfVZYPwalgcE73Z5E14Ud8';
const bot = new TelegramBot(token, {
  polling: true
});
var IdMiChat = 1189408516;
//var SerialPort = require('serialport');
//var MiPuerto = new SerialPort('COM4', {
  //baudRate: 9600,
  //autoOpen: true
var client = mqtt.connect('mqtt://housefox:123andres@broker.shiftr.io')

bot.on('message', (msg) => {
  const chatId = msg.chat.id;
  console.log("El ID del char" + chatId);
  var Mensaje = msg.text.toString().toLocaleLowerCase();
  if (Mensaje.indexOf("encender") >= 1) {
    console.log("encendiendo el led");
     bot.sendMessage(chatId, 'Encendere el led');
    client.publish('/fH/foco/casa', '1')
    //MiPuerto.write("H");
  } else if (Mensaje.indexOf("apagar") >= 0) {
    console.log("Apagar el led");
    bot.sendMessage(chatId, 'Apagare el led');
    client.publish('/fH/foco/casa', '0')
    //MiPuerto.write("L");
  }
  bot.sendMessage(chatId, 'Recibí tu mensaje');

});

//MiPuerto.setEncoding('utf8');

//MiPuerto.on('data', function(data) {
  //console.log("Lo que entro es " + data);
  //if (data[0] == 'H') {
    //console.log("Boton Precionado");
  //  bot.sendMessage(IdMiChat, "Se preciono el boton");
//  }
//});
