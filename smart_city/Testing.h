#pragma once
#include <iostream>
#include "../smart_city/Public/FacilityEntities.h"
#include "../smart_city/Education/EducationEntities.h"
#include "../smart_city/Medicine/HospitalEntities.h"
#include "../smart_city/Commercial/MallEntities.h"
#include "../smart_city/Transport/BusStop.h"
using namespace std;

class EdgeNode {
public:
    EdgeNode* nextEdge;
    double weight;
    GraphNode* to;
    EdgeNode(double w = 0.0) : weight(w), nextEdge(nullptr), to(nullptr){}
};

class GraphManager {
public:
    double threshold;
    string schoolTag;
    string hospitalTag;
    string busStopTag;
    string commercialTag;
    string publicFacilityTag;

    GraphNode* adjacencyList;

    GraphManager(double thresh = 0.0f)
        : threshold(thresh),
        schoolTag("school"),
        hospitalTag("hospital"),
        busStopTag("bus_stop"),
        commercialTag("commercial"),
        publicFacilityTag("public_facility"),
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


    void add(School* toAdd) {
        if (!toAdd) return;

        GraphNode* newNode = new GraphNode();
        newNode->type = schoolTag;
        newNode->ID = toAdd->schoolID;
        newNode->latitude = toAdd->latitude;
        newNode->longitude = toAdd->longitude;

        add(newNode); // insert into graph
    }

    void add(Hospital* toAdd) {
        if (!toAdd) return;

        GraphNode* newNode = new GraphNode();
        newNode->type = hospitalTag;
        newNode->ID = toAdd->id;
        newNode->latitude = toAdd->latitude;
        newNode->longitude = toAdd->longitude;

        add(newNode);
    }

    void add(Facility* toAdd) {
        if (!toAdd) return;

        GraphNode* newNode = new GraphNode();
        newNode->type = publicFacilityTag;
        newNode->ID = toAdd->id;
        newNode->latitude = toAdd->latitude;
        newNode->longitude = toAdd->longitude;

        add(newNode);
    }

    void add(Mall* toAdd) {
        if (!toAdd) return;

        GraphNode* newNode = new GraphNode();
        newNode->type = commercialTag;
        newNode->ID = toAdd->mallId;
        newNode->latitude = toAdd->latitude;
        newNode->longitude = toAdd->longitude;

        add(newNode);
    }

    void add(BusStop* toAdd) {
        if (!toAdd) return;

        GraphNode* newNode = new GraphNode();
        newNode->type = busStopTag;
        newNode->ID = toAdd->stopId;
        newNode->latitude = toAdd->latitude;
        newNode->longitude = toAdd->longitude;
        add(newNode);
    }

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

    GraphNode(string t = "", string id = "", double lat = 0.0, double longi = 0.0)
        : type(t), ID(id),
        next(nullptr),
        latitude(lat),
        longitude(longi),
        nextType(nullptr),
        edgeHead(nullptr) {
    }
};
