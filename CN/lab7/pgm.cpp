#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <regex>

using namespace std;

struct IPAddress {
    unsigned int octets[4];
    int prefix;
};

// Convert the IP to a 32-bit integer
unsigned int ipToInt(const IPAddress& ip) {
    return (ip.octets[0] << 24) | (ip.octets[1] << 16) | 
           (ip.octets[2] << 8) | ip.octets[3];
}

// Validate the CIDR notation
bool validateCIDR(const string& cidr) {
    regex cidrPattern(R"((\d{1,3}\.){3}\d{1,3}\/\d{1,2})");
    if (!regex_match(cidr, cidrPattern)) return false;
    
    size_t slashPos = cidr.find('/');
    string ipPart = cidr.substr(0, slashPos);
    string prefixPart = cidr.substr(slashPos + 1);

    stringstream ss(ipPart);
    string octet;
    int count = 0;
    while (getline(ss, octet, '.')) {
        int value = stoi(octet);
        if (value < 0 || value > 255) return false;
        count++;
    }
    if (count != 4) return false;  // Ensure 4 octets

    try {
        int prefix = stoi(prefixPart);
        if (prefix < 0 || prefix > 32) return false;
    } catch (const exception& e) {
        return false;  // Invalid prefix part
    }

    return true;
}

// Parse the CIDR and extract IP address and prefix
bool parseCIDR(const string& cidr, IPAddress& ip) {
    size_t slashPos = cidr.find('/');
    if (slashPos == string::npos) return false;

    string ipPart = cidr.substr(0, slashPos);
    string prefixPart = cidr.substr(slashPos + 1);

    ip.prefix = stoi(prefixPart);
    if (ip.prefix < 0 || ip.prefix > 32) return false;

    stringstream ss(ipPart);
    string octet;
    int count = 0;

    while (getline(ss, octet, '.')) {
        int value = stoi(octet);
        if (value < 0 || value > 255) return false;
        ip.octets[count] = value;
        count++;
    }
    return count == 4;
}

// Validate if the given IP is within the CIDR range
bool isIPInRange(const IPAddress& ip, const IPAddress& networkIP) {
    unsigned int ipNum = ipToInt(ip);
    unsigned int networkNum = ipToInt(networkIP);
    
    unsigned int mask = ~((1U << (32 - networkIP.prefix)) - 1);
    
    // Check if the IP is in range by comparing after applying the subnet mask
    return (ipNum & mask) == (networkNum & mask);
}

// Get the total number of addresses in a subnet
unsigned int getTotalAddresses(int hosts) {
    return pow(2, ceil(log2(hosts + 2)));
}

// Calculate and display subnet details
void calculateSubnets(const IPAddress& ip, int numSubnets, const vector<int>& desiredHosts) {
    unsigned int totalHosts = pow(2, 32 - ip.prefix);
    unsigned int ipNum = ipToInt(ip);

    unsigned int mask = ~((1U << (32 - ip.prefix)) - 1);
    unsigned int network = ipNum & mask;
    unsigned int broadcast = network | ~mask;

    cout << "\nOriginal Subnet Information:\n";
    cout << "Network Address: " << (network >> 24) << "." << ((network >> 16) & 255) << "."
         << ((network >> 8) & 255) << "." << (network & 255) << endl;
    cout << "Broadcast Address: " << (broadcast >> 24) << "." << ((broadcast >> 16) & 255) << "."
         << ((broadcast >> 8) & 255) << "." << (broadcast & 255) << endl;
    cout << "Total Addresses: " << totalHosts << endl;
    cout << "Usable Host Addresses: " << (totalHosts - 2) << endl;

    unsigned int totalAddressesNeeded = 0;
    vector<unsigned int> subnetSizes(numSubnets);
    for (int i = 0; i < numSubnets; i++) {
        subnetSizes[i] = getTotalAddresses(desiredHosts[i]);
        totalAddressesNeeded += subnetSizes[i];
    }

    if (totalAddressesNeeded > totalHosts) {
        cout << "\nError: Total addresses needed (" << totalAddressesNeeded 
             << ") exceeds available addresses (" << totalHosts << ")\n";
        return;
    }

    cout << "\nSubnet Configurations:\n";
    unsigned int currentAddress = ipNum;
    unsigned int endRange = network + totalHosts - 1;  // Max valid range for this network

    for (int i = 0; i < numSubnets; i++) {
        unsigned int subnetStart = currentAddress;
        unsigned int subnetEnd = subnetStart + subnetSizes[i] - 1;

        // Check if the subnet end exceeds the available range
        if (subnetEnd > endRange) {
            cout << "Error: Subnet exceeds available IP range. Exiting program.\n";
            return;
        }

        int newPrefix = 32 - log2(subnetSizes[i]);

        cout << "Subnet " << i + 1 << " (/" << newPrefix << "):\n";
        cout << "  Hosts: " << desiredHosts[i] << endl;
        cout << "  Start: " << (subnetStart >> 24) << "." << ((subnetStart >> 16) & 255) << "."
             << ((subnetStart >> 8) & 255) << "." << (subnetStart & 255) << endl;
        cout << "  End: " << (subnetEnd >> 24) << "." << ((subnetEnd >> 16) & 255) << "."
             << ((subnetEnd >> 8) & 255) << "." << (subnetEnd & 255) << endl;

        currentAddress += subnetSizes[i];
    }

    if (currentAddress - ipNum < totalHosts) {
        cout << "\nRemaining unused addresses: " << (totalHosts - (currentAddress - ipNum)) << endl;
    }
}

int main() {
    string cidr;
    IPAddress ip;
    int numSubnets;
    
    cout << "Enter CIDR IP address (e.g., 10.20.127.10/18): ";
    getline(cin, cidr);

    // Validate CIDR notation before proceeding
    if (!validateCIDR(cidr)) {
        cout << "Invalid CIDR notation! Please use format xxx.xxx.xxx.xxx/nn\n";
        return 1;
    }

    if (!parseCIDR(cidr, ip)) {
        cout << "Invalid CIDR notation! Please use format xxx.xxx.xxx.xxx/nn\n";
        return 1;
    }

    // Validate that the IP is within the range
    unsigned int ipNum = ipToInt(ip);
    unsigned int mask = ~((1U << (32 - ip.prefix)) - 1);
    unsigned int network = ipNum & mask;

    IPAddress networkIP = ip;
    networkIP.octets[0] = (network >> 24) & 255;
    networkIP.octets[1] = (network >> 16) & 255;
    networkIP.octets[2] = (network >> 8) & 255;
    networkIP.octets[3] = network & 255;

    // Check if the given IP is within the network range
    if (!isIPInRange(ip, networkIP)) {
        cout << "Error: The IP " << cidr.substr(0, cidr.find('/')) << " is not within the range defined by CIDR "
             << cidr << "\n";
        return 1;
    }

    cout << "Network Address: " << networkIP.octets[0] << "." << networkIP.octets[1] << "."
         << networkIP.octets[2] << "." << networkIP.octets[3] << endl;

    cout << "Enter number of subnets: ";
    cin >> numSubnets;

    if (numSubnets <= 0) {
        cout << "Error: Number of subnets must be positive!\n";
        return 1;
    }

    vector<int> desiredHosts(numSubnets);
    for (int i = 0; i < numSubnets; i++) {
        cout << "hosts for subnet " << i + 1 << ": ";
        cin >> desiredHosts[i];
        if (desiredHosts[i] <= 0) {
            cout << "Error: Number of hosts must be positive!\n";
            return 1;
        }
    }

    calculateSubnets(ip, numSubnets, desiredHosts);

    return 0;
}
