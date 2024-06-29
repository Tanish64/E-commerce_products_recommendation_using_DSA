#include<iostream>
#include<set>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;

// creating map data structure to store 
// products purchased by user
map<string,vector<string> > user;

// creating vector for storing the products that we have
vector<string> products;

void stock_filling(){
    // filling users entries
    user["user1"].push_back("product1");
    user["user1"].push_back("product2");
    user["user1"].push_back("product4");
    user["user1"].push_back("product5");

    user["user2"].push_back("product1");
    user["user2"].push_back("product3");

    user["user3"].push_back("product4");
    user["user3"].push_back("product3");
    user["user3"].push_back("product5");

    user["user4"].push_back("product1");
    user["user4"].push_back("product3");
    user["user4"].push_back("product5");

    user["user5"].push_back("product3");
    user["user5"].push_back("product4");

    // filling the invertory(products)
    products.push_back("product1");
    products.push_back("product2");
    products.push_back("product3");
    products.push_back("product4");
    products.push_back("product5");


}

// using jaccard similarity concept to calculate 
// similarities between the users 
// jaccard similarity = ratio of intersetion and union of users products set

double jaccard_similarity(vector<string> &first_user,vector<string> &second_user){
    // using set datastructure to store the products array
    set<string> set_first_user(first_user.begin(),first_user.end());
    set<string> set_second_user(second_user.begin(),second_user.end());

    // creating set for intersection 
    set<string> intersection;
    set_intersection(set_first_user.begin(), set_first_user.end(), set_second_user.begin(), set_second_user.end(),inserter(intersection , intersection.begin()));

    //creating set for union 
    set<string> union_set;
    set_union(set_first_user.begin(), set_first_user.end(), set_second_user.begin(), set_second_user.end(), inserter(union_set , union_set.begin())); 

    return (double)intersection.size()/union_set.size();
}


// finding the user having similarity to the target user 
string similar_user(string &target_user,map<string,vector<string> > &user){
    double max_similar = 0.0;
    string most_similar_user;
    // creating iterator for the map
    map<string,vector<string> > :: iterator it;
    for(it = user.begin() ; it != user.end();it++){
        if(it->first == target_user){
            continue;
        }

        double similarity = jaccard_similarity(user.at(target_user),it->second);

        if(similarity > max_similar){
            max_similar = similarity;
            most_similar_user = it->first;
        }
    }

    return most_similar_user;

}


// creating function which recommend products to the target user
vector<string> recommend_prod(string target_user,map<string,vector<string> > &user){
    string most_similar_user = similar_user(target_user,user);

    if(most_similar_user.empty()){
        return vector<string> ();
    }
    // history of the target user
    set<string> history_target(user.at(target_user).begin(),user.at(target_user).end());

    // history of the most similar user
    set<string> history_similar_user(user.at(most_similar_user).begin(),user.at(most_similar_user).end());

    // creating recommendation array to return the recommanded products
    vector<string> recommendation;
    // creating interator for set
    set<string>:: iterator it;
    for(it = history_similar_user.begin();it !=history_similar_user.end();it++){
        if(history_target.find(*it) == history_target.end()){
            recommendation.push_back(*it);
        }
    }
    return recommendation;
}



int main(){
    stock_filling();
    string target_user;

    cout<<"Enter the user Id for recommendation : ";
    cin>>target_user;

    if(user.find(target_user) == user.end()){
        cout<<"user not found."<<endl;
    }
    else{
        vector<string> recommendations = recommend_prod(target_user,user);
        if(recommendations.empty()){
            cout<< "No Recommendation available for "<<target_user<<"."<<endl;
        }
        else{
            cout<<"Recommendations for "<<target_user<<": ";
            for(int i=0;i<recommendations.size();i++){
                cout<<recommendations[i]<<" ";
            }
            cout<<endl;
        }
    }

    return 0;

}