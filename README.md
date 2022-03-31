# ChessAI
 C++ Windows Forms application to play Chess with self-training Artificial Intelligence on Monte Carlo Tree  
   
<b><a href="https://github.com/MrAlexeiMK/Chess/raw/main/%D0%A8%D0%B0%D1%85%D0%BC%D0%B0%D1%82%D1%8B%20(%D1%83%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D1%89%D0%B8%D0%BA).msi">DOWNLOAD</b></a>  
  
<b><a href="https://github.com/MrAlexeiMK/Chess">PREVIOUS VERSION</b></a>  
  
Application Data Folder Path is "%appdata%/Chess by MrAlexeiMK" contains langs, weights, settings.txt, mcts.txt (Monte-Carlo Tree) and log.txt 
  
<b>Was used:</b>  
1) https://www.nature.com/articles/nature24270.epdf?author_access_token=VJXbVjaSHxFoctQQ4p2k4tRgN0jAjWel9jnR3ZoTv0PVW4gB86EEpGqTRDtpIz-2rmo8-KG06gqVobU5NSCFeHILHcVFUeMsbvwS-lxjqQGg98faovwjxeTUgZAUMnRQ  
2) https://web.stanford.edu/~surag/posts/alphazero.html  
3) https://habr.com/ru/post/282522/  
4) https://web.archive.org/web/20180623055344/http://mcts.ai/about/index.html  
  
<b>Instructions:</b>  
Main menu:  
<img src="https://user-images.githubusercontent.com/25348980/161140081-a0416ed0-ba0c-49d6-9fb0-664aa720bcb1.png" width="300"></img>  
[Play] - Play by yourself  
[W.csv] [Play against AI] [train] - Play against AI with weights from file "W.csv", select "train" if you want to change your weights during the game  
[W.csv] [Start training] [count] - Train Atrificial Intelligence by playing with itself "count" times with weights from file "W.csv"  
Settings menu:  
<img src="https://user-images.githubusercontent.com/25348980/161140928-59075c0e-d62a-4930-b799-21aeb34e553b.png" width="300"></img>  
[Language] - Select file with language  
[First step] - Select who will go first in "Play against AI"  
[Sound] - Play sound  
[Max. Steps] - Maximum steps in the game (when reached - a draw)  
[Layers] - Layers of your neural network (so far only a simple neural network is supported)  
[Factor] - Learning rate of neural network  
[Simulations] - Number of simulations from unknown position in Monte-Carlo Tree  
[History Steps] - Last how many positions to remember? (if 3 - first layer of neural network should be 256•3=768)  
[Depth] - Depth of simulation (if reached and game is not ended - draw)  
[Max. Depth] - Maximum depth of Monte-Carlo Tree from start node (if average number of moves in a position is 40 and Max. Depth is 8, then 40^7 ≈ 1.6e11 - average count of nodes in Monte-Carlo Tree)  
<b>Documentation:<b>  
<b><a href="https://github.com/MrAlexeiMK/ChessAI/tree/main/Chess">Sources</b></a>  
 [<b>logManager.h</b>]:  
 Static class to print in log.txt  (saves after closing application)  
 ```
#include "logManager.h"
 
logManager::writeln("debug info");
 ```
