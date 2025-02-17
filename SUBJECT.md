# Introduction
Hypertext Transfer Protocol (HTTP) は、分散型で協力的なハイパーメディア情報システムのためのアプリケーションプロトコルです。  
HTTPは、ワールドワイドウェブにおけるデータ通信の基盤であり、ハイパーテキスト文書には他のリソースへのハイパーリンクが含まれています。これにより、ユーザーはウェブブラウザでマウスをクリックしたり画面をタップしたりするだけで簡単にアクセスできます。
HTTPは、ハイパーテキストとワールドワイドウェブを実現するために開発されました。  
ウェブサーバーの主な機能は、ウェブページを保存し、処理し、クライアントに配信することです。クライアントとサーバー間の通信は、ハイパーテキスト転送プロトコル（HTTP）を使用して行われます。  
配信されるページは主にHTMLドキュメントであり、テキストコンテンツに加えて、画像、スタイルシート、スクリプトが含まれる場合があります。  
高トラフィックのウェブサイトでは、複数のウェブサーバーが使用されることがあります。
ユーザーエージェント（一般的にはウェブブラウザやウェブクローラー）は、HTTPを使用して特定のリソースを要求することで通信を開始します。サーバーはそのリソースの内容を返すか、処理できない場合はエラーメッセージを返します。リソースは通常、サーバーの補助記憶装置に保存されている実際のファイルですが、必ずしもそうとは限らず、ウェブサーバーの実装方法によって異なります。  
主な機能はコンテンツを配信することですが、HTTPの完全な実装には、クライアントからコンテンツを受信する方法も含まれています。この機能は、ウェブフォームの送信やファイルのアップロードなどに使用されます。  

# Mandatory
>Key | Value
>--- | ---
>Program name|webserv
>Turn in files|Makefile, *.{h, hpp}, *.cpp, *.tpp, *.ipp, configuration files
>Makefile|NAME, all, clean, fclean, re
>Arguments|[A configuration file]
>External functs.|Everything in C++ 98. execve, dup, dup2, pipe, strerror, gai_strerror, errno, dup, dup2, fork, socketpair, htons, htonl, ntohs, ntohl, select, poll, epoll (epoll_create, epoll_ctl, epoll_wait), kqueue (kqueue, kevent), socket, accept, listen, send, recv, chdir bind, connect, getaddrinfo, freeaddrinfo, setsockopt, getsockname, getprotobyname, fcntl, close, read, write, waitpid, kill, signal, access, stat, open, opendir, readdir and closedir.
>Libft authorized|n/a
>Description|A HTTP server in C++ 98

実行可能ファイルは以下のように実行されます：  
`./webserv [設定ファイル]`

# Requirements
- プログラムは、設定ファイルを引数として受け取るか、デフォルトのパスを使用する必要があります。
- 別のウェブサーバーを `execve` で実行してはいけません。
- サーバーは決してブロックしてはいけません。また、必要に応じてクライアントを適切に切断できるようにする必要があります。
- サーバーはノンブロッキングで動作し、クライアントとサーバー間のすべてのI/O操作（リッスンを含む）に対して、`poll()`（または同等の機能）を1つだけ使用しなければなりません。
- `poll()`（または同等の機能）は、読み取りと書き込みを同時にチェックしなければなりません。
- `poll()`（またはそれに相当する機能）は、読み取り操作と書き込み操作を同時に監視できるように設定する必要があります。
- `read` や `write` 操作の後に `errno` の値を確認することは厳禁です。
- 設定ファイルを読み込む前に `poll()`（または同等の機能）を使用する必要はありません。
- `FD_SET`, `FD_CLR`, `FD_ISSET`, `FD_ZERO` などのマクロや定義はすべて使用できます（これらが何を行い、どのように機能するのかを理解することは非常に有用です）。
- サーバーへのリクエストが永遠にハングすることは絶対にあってはなりません。
- サーバーは、任意の選択したウェブブラウザと互換性がなければなりません。
- NGINXはHTTP 1.1に準拠しているものとみなし、ヘッダーや応答の動作を比較するために使用することができます。
- HTTP応答のステータスコードは正確でなければなりません。
- サーバーは、エラーページが提供されていない場合にデフォルトのエラーページを持っていなければなりません。
- `fork` を使用できるのは、CGI（例: PHP、Pythonなど）に関連する目的に限られます。
- 完全に静的なウェブサイトを提供できる必要があります。
- クライアントはファイルをアップロードできる必要があります。
- 少なくとも `GET`、`POST`、`DELETE` メソッドをサポートする必要があります。
- サーバーをストレステストし、どのような状況でも利用可能な状態を維持しなければなりません。
- サーバーは複数のポートでリッスンできる必要があります（詳細は設定ファイルを参照）。

# Configuration file
設定ファイルでは以下のことができる必要があります：
- **各サーバーのポートとホストを指定**: サーバーごとに使用するポートとホストを選択できるようにする。
- **`server_names` の設定**: `server_names` を設定するか、設定しないままにすることが可能。
- **デフォルトサーバーの指定**: 指定されたホスト:ポートの最初のサーバーは、そのホスト:ポートのデフォルトサーバーとなり、他のサーバーに属さないすべてのリクエストに応答する。
- **デフォルトのエラーページの設定**: 必要に応じてデフォルトのエラーページを設定可能。
- **クライアントボディサイズの制限**: クライアントのボディサイズを制限できるようにする。
- **ルートを設定する際に、以下のいずれかまたは複数のルール/設定を適用する必要があります（正規表現は使用しません）**
  - ルートに許可されるHTTPメソッドのリストを定義。
  - HTTPリダイレクションを定義。
  - ファイルの検索元となるディレクトリまたはファイルを定義  
  （例: `/kapouet` URLが`/tmp/www`にルートされている場合、`/kapouet/pouic/toto/pouet`は`/tmp/www/pouic/toto/pouet`に対応する）。
  - ディレクトリリスト表示をオンまたはオフに設定。
  - リクエストがディレクトリの場合に応答するデフォルトファイルを設定する必要があります。
  - 特定のファイル拡張子（例: `.php`）に基づいてCGIを実行する必要があります。
  - POSTメソッドとGETメソッドで動作するようにする必要があります。
  - ルートはアップロードされたファイルを受け入れることができ、保存先を設定できる必要があります。
    - **CGIとは何かを考えたことはありますか？**  
    CGI（Common Gateway Interface）は、サーバーが外部プログラムを実行し、その出力をクライアントに返すための仕組みです。
    - **CGIを直接呼び出さない場合の設定**  
    CGIを直接呼び出すのではなく、リクエストされたファイルのフルパスを`PATH_INFO`として渡します。
    - **チャンク化されたリクエストの処理**  
    サーバーはチャンク化されたリクエストをデチャンクし、CGIに渡します。CGIは、ボディの終了をEOF（End Of File）で判断します。
    - **CGIの出力の処理**  
    CGIが`content_length`を返さない場合、EOFがデータ終了を示します。
    - **CGI呼び出し時の設定**  
    プログラムはリクエストされたファイルを最初の引数としてCGIに渡す必要があります。
    - **相対パスへの対応**  
    CGIは相対パスでのファイルアクセスを正しく処理できるよう、適切なディレクトリで実行されなければなりません。
    - **1つのCGIと連携**  
    サーバーは少なくとも1つのCGI（例: `php-CGI`や`Python`など）と正常に動作する必要があります。

すべての機能が評価時に正常に動作することを確認するために、テストおよびデモ用の設定ファイルと基本的なデフォルトファイルを提供する必要があります。
> **EXAMPLE**：
> ```nginx
> server {
>     listen 8080;
>     server_names webserv.local webserv2.local;
>     
>     # / -> /var/www/html/
>     root /var/www/html/;
>     index index.html;
> 
>     location /api/v1/ {
>         # /api/v1/ -> /var/www/api/v1/
>         root /var/www/;
>     }
> 
>     location /api/v2/ {
>         # /api/v2/ -> /var/www/api/v2/
>         alias /var/www/api/v2/;
>         # allowed only GET, HEAD
>         limit_expect GET HEAD {
>             deny all;
>         }
>     }
> 
>     location /redirect/ {
>         return 301 http://google.com;
>     }
> }
> 
> server {
>     listen 8081;
>     server_names webserv3.local webserv4.local;
>     # allowed only GET, POST, DELETE, HEAD
>     limit_expect GET POST DELETE HEAD {
>         deny all;
>     }
> 
>     # / -> /var/www/html/
>     root /var/www/html/;
>     index index.php;
> 
>     location /api/v1/ {
>         # /api/v1/ -> /var/www/api/v1/
>         root /var/www/;
>     }
>     
>     location /api/v2/ {
>         # /api/v2/ -> /var/www/api/v2/
>         alias /var/www/api/v2/;
>         # allowed only GET
>         limit_expect GET {
>             deny all;
>         }
>     }
> 
>     location /redirect/ {
>         return 301 http://microsoft.com;
>     }
> 
>     location /api/v3/*.bla {
>         index index.bla;
>         alias /var/www/api/v3/;
>         cgi_pass /srv/ubuntu_cgi_tester;
>     }
> }
> ```
> **INFO**： 動作に関して疑問がある場合は、自分のプログラムの動作をNGINXの動作と比較するべきです。たとえば、`server_name`がどのように機能するかを確認するなどです。
> また、簡易的なテスターを提供しています。これは必須ではありませんが、ブラウザやテストで問題なく動作している場合でも、バグを見つける際に役立つかもしれません。
> 

# Bonus part

追加可能な拡張機能として以下を実装できます：

- **クッキーおよびセッション管理のサポート**
  クッキーやセッションをサポートし、簡単な例を準備すること。たとえば、クライアントの識別やセッションデータの保存を行う機能を追加。

- **複数のCGIの対応**
  サーバーが複数のCGIを処理できるようにする。たとえば、`.php`ファイル用の`php-CGI`と、`.py`ファイル用の`Python CGI`を同時にサポートする設定を提供。
