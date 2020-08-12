const TelegramBot = require('node-telegram-bot-api');


const token = '1093970624:AAGv5-k6E53uApfVZYPwalgcE73Z5E14Ud8';


const bot = new TelegramBot(token, {polling: true});


});

bot.on('message', (msg) => {
  const chatId = msg.chat.id;
  var Mensaje = msg.text;
  if (Mensaje == "encender"){
    console.log("encender el led")
      bot.sendMessage(chatId, 'encendere el led ');
    }
    else if(Mensaje == "apagar"){
    console.log("apagar led");
      bot.sendMessage(chatId, 'apagare el led ');
    }
  bot.sendMessage(chatId, 'Recibí tu mensaje ');
});
