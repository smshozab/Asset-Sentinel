# Asset-Sentinel
A Data Structures project in which we are using Vectors, Arrays, Sorting, Searching, Mapping, Hashing, etc in tokenization and digital asset management which involves representing real-world assets (such as debts or real estate) as digital tokens.

# Tokenization &amp; Digital Asset Management (Supply Chain Instantiation)

This project implements data structure concepts in C++ by solving the real-world supply chain problem or, better to say, the Cash Flow of assets. It provides functionalities for managing tokens and products within a supply chain, facilitating secure transactions, and tracking product movements like Manufacturers, suppliers, Distributors, Regulatory Bodies, Consumers, etc.

## Features

- **Token Management**: Issue tokens representing ownership stakes in the supply chain entities.
- **Product Tracking**: Track the movement of products through different stages of the supply chain.
- **Token Transactions**: Facilitate secure and efficient transfer of ownership tokens between entities using SHA-256.
- **Product Transfers**: Enable the transfer of product ownership between different stages or owners in the supply chain.
- **Merkle Tree Integration**: Utilize a Merkle tree to create a tamper-evident log of token transactions, ensuring the integrity and immutability of the transaction history.

## How to Use

1. Clone the repository to your local machine:

git clone https://github.com/smshozab/Asset-Sentinel.git

2. Compile the C++ source code using a C++ compiler such as g++:

g++ -o supply_chain supply_chain.cpp

3. Run the compiled executable:

./supply_chain

4. Follow the prompts to issue tokens, products, transfer tokens, transfer products, and view the token transactions Merkle tree.

## Example Use Case

The supply chain management system can be applied in various industries, including pharmaceuticals, manufacturing, logistics, and retail. For example, in the pharmaceutical industry, the system can track the movement of medications from manufacturers to distributors to pharmacies, ensuring transparency and accountability in the supply chain.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

