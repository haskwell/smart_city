#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

//forward declaration
class GraphNode;

class EdgeNode {
public:
    EdgeNode* nextEdge;
    double weight;
    GraphNode* to;
    EdgeNode(double w = 0.0) : weight(w), nextEdge(nullptr), to(nullptr){}
};

class GraphNode {
public:
    string type;
    string ID;
    double latitude;
    double longitude;

    GraphNode* next;        //Next node in the general adjacency list
    GraphNode* nextType;    //Next node of the same type

    EdgeNode* edgeHead;    //Edge list head
    // for Dijkstra's algotithm
    double minDistance;
    GraphNode* previous;
    bool isVisited;
    GraphNode(string t = "", string id = "", double lat = 0.0, double longi = 0.0)
        : type(t), ID(id), next(nullptr), latitude(lat), longitude(longi),
        nextType(nullptr), edgeHead(nullptr),
        // Initialize new variables
        minDistance(1000000000.0), // Initialize to a large number
        previous(nullptr),
        isVisited(false)
    {
    }
};

class GraphManager {
public:
    double threshold;
    string schoolTag;
    string hospitalTag;
    string busStopTag;
    string commercialTag;
    string publicFacilityTag;
	string pharmacyTag;

    GraphNode* adjacencyList;

    GraphManager(double thresh = 1300.0f)
        : threshold(thresh),
        schoolTag("school"),
        hospitalTag("hospital"),
        busStopTag("bus_stop"),
        commercialTag("commercial"),
        publicFacilityTag("public_facility"),
		pharmacyTag("pharmacy"),
        adjacencyList(nullptr)
    {
    }

    void add(GraphNode* toAdd)
    {
        if (!toAdd) return;

        if (!adjacencyList)
        {
            adjacencyList = toAdd;
            return;
        }

        GraphNode* curr = adjacencyList;
        GraphNode* lastOfType = nullptr;
        GraphNode* lastNode = nullptr;

        while (curr)
        {
            lastNode = curr;

            if (curr->type == toAdd->type)
                lastOfType = curr;

            curr = curr->next;
        }

        if (lastOfType)
        {
            while (lastOfType->nextType){
                lastOfType = lastOfType->nextType;
            }

            lastOfType->nextType = toAdd;
        }
        else
        {
            lastNode->next = toAdd;
        }
    }


    void add(string ID, int lat, int longi, string tag) {

        GraphNode* newNode = new GraphNode();
        newNode->type = tag;
        newNode->ID = ID;
        newNode->latitude = lat;
        newNode->longitude = longi;

        add(newNode); // insert into graph
        makeEdge(newNode);
    }

    //void add(Hospital* toAdd) {
    //    if (!toAdd) return;

    //    GraphNode* newNode = new GraphNode();
    //    newNode->type = hospitalTag;
    //    newNode->ID = toAdd->id;
    //    newNode->latitude = toAdd->latitude;
    //    newNode->longitude = toAdd->longitude;

    //    add(newNode);
    //}

    //void add(Facility* toAdd) {
    //    if (!toAdd) return;

    //    GraphNode* newNode = new GraphNode();
    //    newNode->type = publicFacilityTag;
    //    newNode->ID = toAdd->id;
    //    newNode->latitude = toAdd->latitude;
    //    newNode->longitude = toAdd->longitude;

    //    add(newNode);
    //}

    //void add(Mall* toAdd) {
    //    if (!toAdd) return;

    //    GraphNode* newNode = new GraphNode();
    //    newNode->type = commercialTag;
    //    newNode->ID = toAdd->mallId;
    //    newNode->latitude = toAdd->latitude;
    //    newNode->longitude = toAdd->longitude;

    //    add(newNode);
    //}

    //void add(BusStop* toAdd) {
    //    if (!toAdd) return;

    //    GraphNode* newNode = new GraphNode();
    //    newNode->type = busStopTag;
    //    newNode->ID = toAdd->stopId;
    //    newNode->latitude = toAdd->latitude;
    //    newNode->longitude = toAdd->longitude;
    //    add(newNode);
    //}

    double calculateDistance(double x1, double y1, double x2, double y2)
    {
        double deltaX = x2 - x1;
        double deltaY = y2 - y1;
        return sqrt(deltaX * deltaX + deltaY * deltaY);
    }


    void makeEdges() {
        // Start with the head of the adjacency list (all type heads)
        GraphNode* typeHead = adjacencyList;

        // Iterate over each "type head" in the general adjacency list
        while (typeHead)
        {
            // Iterate over every node in the current type chain
            GraphNode* sourceNode = typeHead;
            while (sourceNode)
            {
                // For each source node, we check all possible target nodes
                GraphNode* targetTypeHead = adjacencyList;  // start again from first type head
                while (targetTypeHead)
                {
                    // Iterate over every node in the target type chain
                    GraphNode* targetNode = targetTypeHead;
                    while (targetNode)
                    {
                        // Avoid creating an edge from a node to itself
                        if (sourceNode != targetNode)
                        {
                            // Calculate distance between the source and target node
                            double distance = calculateDistance(
                                sourceNode->latitude, sourceNode->longitude,
                                targetNode->latitude, targetNode->longitude
                            );

                            // Only create an edge if the distance is less than the threshold
                            if (distance <= threshold)  
                            {
                                // Create a new edge
                                EdgeNode* newEdge = new EdgeNode(distance);
                                newEdge->to = targetNode;

                                // Insert the edge at the head of the source node's adjacency list
                                newEdge->nextEdge = sourceNode->edgeHead;
                                sourceNode->edgeHead = newEdge;
                            }
                        }

                        // Move to the next node in the same type chain
                        targetNode = targetNode->nextType;
                    }

                    // Move to the next type head in the global adjacency list
                    targetTypeHead = targetTypeHead->next;
                }

                // Move to the next node in the same type chain as source
                sourceNode = sourceNode->nextType;
            }

            // Move to the next type head in the global adjacency list
            typeHead = typeHead->next;
        }

    }

    void makeEdge(GraphNode* src)
    {
        if (!src) return;

        GraphNode* typeHead = adjacencyList;

        while (typeHead)
        {
            GraphNode* target = typeHead;

            while (target)
            {
                if (target != src)
                {
                    double distance = calculateDistance(
                        src->latitude, src->longitude,
                        target->latitude, target->longitude
                    );

                    if (distance <= threshold)
                    {
                        //source to target edge
                        EdgeNode* e1 = new EdgeNode(distance);
                        e1->to = target;
                        e1->nextEdge = src->edgeHead;
                        src->edgeHead = e1;

                        //target to source edge
                        EdgeNode* e2 = new EdgeNode(distance);
                        e2->to = src;
                        e2->nextEdge = target->edgeHead;
                        target->edgeHead = e2;
                    }
                }

                target = target->nextType;
            }

            typeHead = typeHead->next;
        }
    }

    void printEntireGraph() {
        if (!adjacencyList) {
            cout << "Graph is empty." << endl;
            return;
        }

        GraphNode* typeHead = adjacencyList;

        // Iterate over all type heads in the general adjacency list
        while (typeHead) {
            GraphNode* node = typeHead;

            // Iterate through nodes of the same type
            while (node) {
                cout << "Node ID: " << node->ID << ", Type: " << node->type
                    << ", Coordinates: (" << node->latitude << ", " << node->longitude << ")" << endl;

                EdgeNode* edge = node->edgeHead;
                if (!edge) {
                    cout << "  No edges." << endl;
                }
                else {
                    cout << "  Edges:" << endl;
                    while (edge) {
                        cout << "    -> " << edge->to->ID
                            << " (" << edge->to->type << ")"
                            << ", Weight: " << edge->weight << endl;
                        edge = edge->nextEdge;
                    }
                }

                node = node->nextType;
            }

            typeHead = typeHead->next;
        }

        showGraph();
    }

    void drawGraph(GraphManager& gm, sf::RenderWindow& window) {
        float nodeRadius = 12.0f;
        float scale = 0.1f;
        float offsetX = 100.0f;
        float offsetY = 100.0f;
        // First, draw edges
        GraphNode* typeHead = gm.adjacencyList;
        while (typeHead) {
            GraphNode* node = typeHead;
            while (node) {
                sf::Vector2f srcPos = mapToScreen(node->latitude, node->longitude);

                EdgeNode* edge = node->edgeHead;
                while (edge) {
                    sf::Vector2f dstPos = mapToScreen(edge->to->latitude, edge->to->longitude);

                    sf::Vertex line[] = {
                        sf::Vertex(srcPos, sf::Color::White),
                        sf::Vertex(dstPos, sf::Color::White)
                    };

                    window.draw(line, 2, sf::Lines);
                    edge = edge->nextEdge;
                }

                node = node->nextType;
            }
            typeHead = typeHead->next;
        }

        // Then draw nodes on top of edges
        typeHead = gm.adjacencyList;
        while (typeHead) {
            GraphNode* node = typeHead;
            while (node) {
                sf::Vector2f pos = mapToScreen(node->latitude, node->longitude);

                sf::CircleShape c(nodeRadius);
                c.setOrigin(nodeRadius, nodeRadius);
                c.setFillColor(getColor(node->type));
                c.setPosition(pos);
                window.draw(c);

                node = node->nextType;
            }
            typeHead = typeHead->next;
        }

        // Draw legend/key in bottom-right
        static sf::Font font;
        static bool loaded = false;
        if (!loaded) {
            font.loadFromFile("arial.ttf"); // make sure arial.ttf is in your project folder
            loaded = true;
        }

        float keyX = 1050.0f; // bottom-right x
        float keyY = 700.0f;  // bottom-right y
        float spacing = 30.0f;

        struct LegendItem { string type; sf::Color color; };
        LegendItem items[] = {
            {schoolTag, getColor(schoolTag)},
            {hospitalTag, getColor(hospitalTag)},
            {busStopTag, getColor(busStopTag)},
            {commercialTag, getColor(commercialTag)},
            {publicFacilityTag, getColor(publicFacilityTag)},
            {pharmacyTag, getColor(pharmacyTag)}
        };

        for (int i = 0; i < 6; ++i) {
            // Draw colored circle
            sf::CircleShape c(nodeRadius / 2);
            c.setOrigin(nodeRadius / 2, nodeRadius / 2);
            c.setFillColor(items[i].color);
            c.setPosition(keyX, keyY + i * spacing);
            window.draw(c);

            // Draw label
            sf::Text label;
            label.setFont(font);
            label.setString(items[i].type);
            label.setCharacterSize(18);
            label.setFillColor(sf::Color::White);
            label.setPosition(keyX + nodeRadius + 10, keyY + i * spacing - nodeRadius / 2);
            window.draw(label);
        }
    }

    sf::Vector2f mapToScreen(double lat, double lon) const {
        float scale = 0.1f;
        float offsetX = 100.0f;
        float offsetY = 100.0f;

        return sf::Vector2f(
            static_cast<float>(lat * scale + offsetX),
            static_cast<float>(lon * scale + offsetY)
        );
    }

    sf::Color getColor(const string& type) const {
        if (type == schoolTag) return sf::Color::Blue;
        if (type == hospitalTag) return sf::Color::Red;
        if (type == busStopTag) return sf::Color::Yellow;
        if (type == commercialTag) return sf::Color::Magenta;
        if (type == publicFacilityTag) return sf::Color::Green;
        if (type == pharmacyTag) return sf::Color::Cyan;
        return sf::Color::White;
    }

    void showGraph() {
        sf::RenderWindow window(sf::VideoMode(1200, 900), "Graph Viewer");

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear(sf::Color(30, 50, 70));

            drawGraph(*this, window);
            window.display();
        }
    }

};

