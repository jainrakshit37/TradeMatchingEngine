📊 Trade Matching Engine

A high-performance limit order matching engine implemented in C++.
The system simulates a simplified exchange order book with price-time priority (FIFO), supporting order placement, modification, cancellation, and execution.

🚀 Features
FIFO matching within price levels
Buy/Sell order book using map + queue
Order modify & cancel support
Partial fills + lazy deletion

⚙️ Matching Rule
best_buy_price >= best_sell_price

🛠️ Run
g++ main.cpp orderbook.cpp -o engine
./engine

📁 Structure
main.cpp
orderbook.h
orderbook.cpp
README.md
