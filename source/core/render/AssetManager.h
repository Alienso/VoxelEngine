//
// Created by Alienson on 16.4.2024..
//

#ifndef INC_3DTEST_ASSETMANAGER_H
#define INC_3DTEST_ASSETMANAGER_H

#include <unordered_map>
#include <iostream>

template <typename T>
class AssetManager {
public:

    AssetManager() = default;
    ~AssetManager(){
        for (auto tex : assetsMap){
            delete tex.second;
        }
    }

    [[nodiscard]] T* getAsset(const char *id){
        if (assetsMap.find(id) == assetsMap.end())
            return nullptr;
        return assetsMap[id];
    }

    template<typename... Args>
    [[maybe_unused]] T& createAsset(const char* id, Args&&... args){
        if (assetsMap.find(id) != assetsMap.end()){
            std::cout << "Asset " << id << " already in memory!\n";
            return *assetsMap[id];
        }
        T* asset = new T(args...);
        assetsMap[id] = asset;
        return *asset;
    }

private:
    std::unordered_map<const char*, T*> assetsMap;
};

#endif //INC_3DTEST_ASSETMANAGER_H
