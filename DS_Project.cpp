#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <array>
#include <sstream>
#include <iomanip>

using namespace std;

// Define a struct to represent a token
struct Token {
    string id;      // Token ID
    string owner;   // Owner of the token
    int balance;    // Token balance

    // Constructor
    Token(const string& _id, const string& _owner, int _balance) : id(_id), owner(_owner), balance(_balance) {}

    // Transfer tokens to another owner
    bool transfer(const string& newOwner, int amount) {
        if (amount > balance) {
            cout << "Insufficient balance for transfer." << endl;
            return false;
        }
        owner = newOwner;
        balance -= amount;
        cout << amount << " tokens transferred to " << newOwner << endl;
        return true;
    }

    // Get token balance
    int getBalance() const {
        return balance;
    }
};

// Right rotate function
uint32_t rightRotate(uint32_t value, uint32_t count) {
    return (value >> count) | (value << (32 - count));
}


// Function to compute SHA-256 hash of a string
string sha256(const string& input) {
    array<uint8_t, 32> hash;
    uint8_t buffer[input.size()];
    copy(input.begin(), input.end(), buffer);

    // Initialize SHA-256 context
    uint32_t state[8];
    state[0] = 0x6a09e667;
    state[1] = 0xbb67ae85;
    state[2] = 0x3c6ef372;
    state[3] = 0xa54ff53a;
    state[4] = 0x510e527f;
    state[5] = 0x9b05688c;
    state[6] = 0x1f83d9ab;
    state[7] = 0x5be0cd19;

    // Constants
    const uint32_t k[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    uint64_t ml = input.size() * 8; // Message length in bits

    // Pre-processing
    buffer[input.size()] = 0x80; // Append single '1' bit
    for (int i = input.size() + 1; i < 64; ++i) {
        buffer[i] = 0x00; // Pad with zeros
    }

    // Append original message length in bits
    for (int i = 56; i < 64; ++i) {
        buffer[i] = ml >> ((63 - i) * 8) & 0xff;
    }

    // Process message in 512-bit chunks
    for (int i = 0; i < input.size() + 1; i += 64) {
        uint32_t w[64];

        // Prepare message schedule
        for (int t = 0; t < 16; ++t) {
            w[t] = (buffer[i + (t * 4) + 0] << 24) |
                   (buffer[i + (t * 4) + 1] << 16) |
                   (buffer[i + (t * 4) + 2] << 8) |
                   (buffer[i + (t * 4) + 3]);
        }
        for (int t = 16; t < 64; ++t) {
            uint32_t s0 = (rightRotate(w[t - 15], 7) ^ rightRotate(w[t - 15], 18) ^ (w[t - 15] >> 3));
            uint32_t s1 = (rightRotate(w[t - 2], 17) ^ rightRotate(w[t - 2], 19) ^ (w[t - 2] >> 10));
            w[t] = w[t - 16] + s0 + w[t - 7] + s1;
        }

        // Initialize working variables
        uint32_t a = state[0];
        uint32_t b = state[1];
        uint32_t c = state[2];
        uint32_t d = state[3];
        uint32_t e = state[4];
        uint32_t f = state[5];
        uint32_t g = state[6];
        uint32_t h = state[7];

        // Compression function main loop
        for (int t = 0; t < 64; ++t) {
            uint32_t S1 = (rightRotate(e, 6) ^ rightRotate(e, 11) ^ rightRotate(e, 25));
            uint32_t ch = ((e & f) ^ ((~e) & g));
            uint32_t temp1 = h + S1 + ch + k[t] + w[t];
            uint32_t S0 = (rightRotate(a, 2) ^ rightRotate(a, 13) ^ rightRotate(a, 22));
            uint32_t maj = ((a & b) ^ (a & c) ^ (b & c));
            uint32_t temp2 = S0 + maj;

            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        // Update state
        state[0] += a;
        state[1] += b;
        state[2] += c;
        state[3] += d;
        state[4] += e;
        state[5] += f;
        state[6] += g;
        state[7] += h;
    }

    // Final hash value
    stringstream ss;
    for (int i = 0; i < 8; ++i) {
        ss << hex << setw(8) << setfill('0') << state[i];
    }
    return ss.str();
}

// Define a class for managing tokens
class TokenManager {
private:
    map<string, unique_ptr<Token>> tokens;  // Map to store tokens by ID

    // Merkle Tree Node
    struct MerkleNode {
        string hash;
        unique_ptr<MerkleNode> left;
        unique_ptr<MerkleNode> right;

        MerkleNode(const string& _hash) : hash(_hash), left(nullptr), right(nullptr) {}
    };

    // Utility function to create Merkle Tree
    unique_ptr<MerkleNode> createMerkleTree(const vector<string>& hashes) {
        if (hashes.empty())
            return nullptr;

        if (hashes.size() == 1)
            return make_unique<MerkleNode>(hashes[0]);

        vector<string> nextLevel;
        for (size_t i = 0; i < hashes.size(); i += 2) {
            string combinedHash = hashes[i];
            if (i + 1 < hashes.size())
                combinedHash += hashes[i + 1];
            string hash = sha256(combinedHash);
            nextLevel.push_back(hash);
        }

        return createMerkleTree(nextLevel);
    }

    // Utility function to print Merkle Tree
    void printMerkleTree(const unique_ptr<MerkleNode>& root, int depth = 0) {
        if (!root)
            return;

        cout << string(depth, '-') << root->hash << endl;
        printMerkleTree(root->left, depth + 1);
        printMerkleTree(root->right, depth + 1);
    }

public:
    // Issue a new token
    void issueToken(const string& id, const string& owner, int initialBalance) {
        unique_ptr<Token> newToken = make_unique<Token>(id, owner, initialBalance);
        tokens[id] = move(newToken);
        cout << "Token " << id << " issued to " << owner << " with initial balance " << initialBalance << endl;
    }

    // Transfer tokens
    void transferToken(const string& tokenId, const string& sender, const string& receiver, int amount) {
        if (tokens.find(tokenId) == tokens.end()) {
            cout << "Token with ID " << tokenId << " not found." << endl;
            return;
        }
        Token& token = *tokens[tokenId];
        if (token.owner != sender) {
            cout << "Sender does not own the token." << endl;
            return;
        }
        if (!token.transfer(receiver, amount)) {
            cout << "Token transfer failed." << endl;
            return;
        }
    }

    // Get token balance for a specific owner
    int getTokenBalance(const string& tokenId, const string& owner) const {
        if (tokens.find(tokenId) == tokens.end()) {
            cout << "Token with ID " << tokenId << " not found." << endl;
            return -1;
        }
        const Token& token = *tokens.at(tokenId);
        if (token.owner != owner) {
            cout << "Owner does not own the token." << endl;
            return -1;
        }
        return token.getBalance();
    }

    // Build and print Merkle Tree of token transactions
    void printTokenTransactionsMerkleTree() {
        vector<string> transactionHashes;
        for (const auto& pair : tokens) {
            const Token& token = *pair.second;
            stringstream ss;
            ss << token.id << token.owner << token.balance;
            string hash = sha256(ss.str());
            transactionHashes.push_back(hash);
        }

        unique_ptr<MerkleNode> root = createMerkleTree(transactionHashes);
        cout << "Token Transactions Merkle Tree:" << endl;
        printMerkleTree(root);
    }
};

int main() {
    // Create a token manager instance
    TokenManager tokenManager;

    // Issue some tokens
    tokenManager.issueToken("ABC", "Alice", 100);
    tokenManager.issueToken("XYZ", "Bob", 50);

    // Transfer tokens
    tokenManager.transferToken("ABC", "Alice", "Bob", 30);

    // Print token transactions Merkle Tree
    tokenManager.printTokenTransactionsMerkleTree();

    return 0;
}
