
const TelegramBot = require('node-telegram-bot-api');

const token = '1093970624:AAGv5-k6E53uApfVZYPwalgcE73Z5E14Ud8';

const bot = new TelegramBot(token, {polling: true});

var SerialPort = require('serialport')
var Mipuerto = new SerialPort('/dev/tty-COM4', {
  baudRate: 9600,
  autoOpen: true
})


bot.on('message', (msg) => {
  const chatId = msg.chat.id;
  console.log("El ID del char" + chatId);
  var Mensaje = msg.text;
  if (Mensaje == "Encender"){
    console.log("encender el led")
      bot.sendMessage(chatId, 'encendere el led ');
      Mipuerto.write("H");
    }
    else if(Mensaje == "Apagar"){
    console.log("apagar led");
      bot.sendMessage(chatId, 'apagare el led ');
      Mipuerto.write("L");
    }
  bot.sendMessage(chatId, 'Recibí tu mensaje ');
});
