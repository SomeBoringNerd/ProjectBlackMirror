FROM node:16

WORKDIR /usr/src/app

COPY package*.json ./

RUN /bin/bash npm install

COPY . .

EXPOSE 1984

CMD [ "node", "index.js" ]