# echoskills
A really really really crappy repo for how I use echo skills


I run an nginx server with spawn-fcgi and curl that points to my c++ application. 

Here is my nginx.conf:

  user www-data;
  worker_processes 4;
  pid /run/nginx.pid;
  
  events {
    worker_connections 1024;
  }
  
  http {
  
    include blockips.conf;
  
    server {
      listen 80;
      server_name localhost;
  
      location / {
        fastcgi_pass   127.0.0.1:8000;
  
        fastcgi_param  GATEWAY_INTERFACE  CGI/1.1;
        fastcgi_param  SERVER_SOFTWARE    nginx;
        fastcgi_param  QUERY_STRING       $query_string;
        fastcgi_param  REQUEST_METHOD     $request_method;
        fastcgi_param  CONTENT_TYPE       $content_type;
        fastcgi_param  CONTENT_LENGTH     $content_length;
        fastcgi_param  SCRIPT_FILENAME    $document_root$fastcgi_script_name;
        fastcgi_param  SCRIPT_NAME        $fastcgi_script_name;
        fastcgi_param  REQUEST_URI        $request_uri;
        fastcgi_param  DOCUMENT_URI       $document_uri;
        fastcgi_param  DOCUMENT_ROOT      $document_root;
        fastcgi_param  SERVER_PROTOCOL    $server_protocol;
        fastcgi_param  REMOTE_ADDR        $remote_addr;
        fastcgi_param  REMOTE_PORT        $remote_port;
        fastcgi_param  SERVER_ADDR        $server_addr;
        fastcgi_param  SERVER_PORT        $server_port;
        fastcgi_param  SERVER_NAME        $server_name;
      }
  
    }
  }



run application: 
  spawn-fcgi -p 8000 -n echo_server

More information to come.
