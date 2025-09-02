#include <Python.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>

// ZRDDS headers
#include "ZRDDSCppSimpleInterface.h"
#include "ZRBuiltinTypesTypeSupport.h"
#include "Topic.h"
#include "TopicDescription.h"
#include "ContentFilteredTopic.h"
#include "MultiTopic.h"
#include "TypeSupport.h"
#include "DomainEntity.h"
#include "ReturnCode_t.h"
#include "DomainParticipantFactory.h"
#include "ZRDDSCppWrapper.h"

namespace py = pybind11;

// Global storage for Topic-related DDS entities
struct TopicManager {
    static std::map<int, DDS::DomainParticipant*> participants;
    static std::map<std::string, DDS::Topic*> topics;
    static std::map<std::string, DDS::ContentFilteredTopic*> content_filtered_topics;
    static std::map<std::string, DDS::MultiTopic*> multi_topics;
    static std::map<std::string, DDS::TypeSupport*> type_supports;
    
    static int next_id;
    
    static int generate_id() { return ++next_id; }
    
    static void cleanup() {
        DDS::DomainParticipantFactory *factory = DDS::DomainParticipantFactory::get_instance();
        
        // Clean up topics
        for (auto& pair : topics) {
            if (pair.second) {
                // Topic deletion is handled by DomainParticipant
            }
        }
        
        // Clean up content filtered topics
        for (auto& pair : content_filtered_topics) {
            if (pair.second) {
                // ContentFilteredTopic deletion is handled by DomainParticipant
            }
        }
        
        // Clean up multi topics
        for (auto& pair : multi_topics) {
            if (pair.second) {
                // MultiTopic deletion is handled by DomainParticipant
            }
        }
        
        // Clean up type supports
        for (auto& pair : type_supports) {
            if (pair.second) {
                // TypeSupport is typically static, no need to delete
            }
        }
        
        // Delete participants and their contained entities
        for (auto& pair : participants) {
            if (pair.second) {
                pair.second->delete_contained_entities();
                if (factory) {
                    factory->delete_participant(pair.second);
                }
            }
        }
        
        // Clear all maps
        participants.clear();
        topics.clear();
        content_filtered_topics.clear();
        multi_topics.clear();
        type_supports.clear();
    }
};

std::map<int, DDS::DomainParticipant*> TopicManager::participants;
std::map<std::string, DDS::Topic*> TopicManager::topics;
std::map<std::string, DDS::ContentFilteredTopic*> TopicManager::content_filtered_topics;
std::map<std::string, DDS::MultiTopic*> TopicManager::multi_topics;
std::map<std::string, DDS::TypeSupport*> TopicManager::type_supports;
int TopicManager::next_id = 1000;

// Get participant factory function
py::capsule get_participant_factory()
{
    DDS::DomainParticipantFactory *factory = DDS::DomainParticipantFactory::get_instance();
    if (!factory)
    {
        throw std::runtime_error("Failed to get DomainParticipantFactory instance");
    }
    return py::capsule(factory, [](void *p) {});
}

// Refactored Topic module wrapper - Focused on Topic functionality only
PYBIND11_MODULE(_zrdds_topic, m) {
    m.doc() = "ZRDDS Python Wrapper - Topic Module (Focused on Topic functionality)";
    
    // Basic functions
    m.def("hello", []() {
        return "Hello from ZRDDS Topic Module - Focused on Topic functionality!";
    });
    
    m.def("get_version", []() {
        return "ZRDDS Topic Module v2.1.0 - Topic-focused implementation";
    });
    
    // Get participant factory
    m.def("get_participant_factory", &get_participant_factory, "Get DomainParticipantFactory instance");
    
    // Initialize Topic module
    m.def("init", []() {
        DDS::DomainParticipantFactory *factory = DDS::DomainParticipantFactory::get_instance();
        if (factory) {
            TopicManager::cleanup();
            return true;
        } else {
            return false;
        }
    }, "Initialize ZRDDS Topic system");
    
    // Create domain participant
    m.def("create_domain_participant", [](int domain_id, const std::string& qos_name = "") {
        DDS::DomainParticipantFactory *factory = DDS::DomainParticipantFactory::get_instance();
        if (!factory) {
            return -1;
        }
        
        // Check if participant already exists for this domain
        if (TopicManager::participants.find(domain_id) != TopicManager::participants.end()) {
            return domain_id; // Already exists
        }
        
        // Create participant with default QoS
        DDS::DomainParticipant* participant = factory->create_participant(
            domain_id, 
            DDS::DOMAINPARTICIPANT_QOS_DEFAULT, 
            nullptr, 
            DDS::STATUS_MASK_NONE
        );
        
        if (participant) {
            TopicManager::participants[domain_id] = participant;
            return domain_id;
        } else {
            return -1;
        }
    }, py::arg("domain_id"), py::arg("qos_name") = "", "Create domain participant");
    
    // Create Topic (pure Topic creation, no DataWriter)
    m.def("create_topic", [](int domain_id, const std::string& topic_name, 
                             const std::string& type_name = "Bytes") -> int {
        auto participant_it = TopicManager::participants.find(domain_id);
        if (participant_it == TopicManager::participants.end()) {
            return -1; // Participant not found
        }
        
        DDS::DomainParticipant* participant = participant_it->second;
        
        // Check if topic already exists
        auto topic_it = TopicManager::topics.find(topic_name);
        if (topic_it != TopicManager::topics.end()) {
            return 0; // Topic already exists
        }
        
        // Register type support first
        DDS::ReturnCode_t register_result = DDS::BytesTypeSupport::get_instance()->register_type(
            participant,
            type_name.c_str()
        );
        
        if (register_result != DDS::RETCODE_OK) {
            return -1; // Failed to register type
        }
        
                 // Create topic with properly initialized QoS
         DDS::TopicQos topic_qos;
         DDS_DefaultTopicQosInitial(&topic_qos);
         
         DDS::Topic* topic = participant->create_topic(
             topic_name.c_str(), 
             type_name.c_str(),
             topic_qos, 
             nullptr, 
             DDS::STATUS_MASK_NONE
         );
        
        if (topic) {
            TopicManager::topics[topic_name] = topic;
            return 1; // Topic created successfully
        } else {
            return -1; // Failed to create topic
        }
    }, py::arg("domain_id"), py::arg("topic_name"), py::arg("type_name") = "Bytes", 
       "Create Topic (returns 1=created, 0=exists, -1=error)");
    
    // ID-based Topic creation - no pointer passing needed
    m.def("create_topic_with_participant_id", [](int participant_id, const std::string& topic_name, 
                                                 const std::string& type_name = "Bytes") -> int {
        // We need to get the participant pointer from domain module
        // For now, we'll use a simplified approach - get the participant pointer
        // This is a temporary solution until we implement proper cross-module communication
        
        // Import domain module to get participant pointer
        // This is a workaround - in a real implementation, we'd have better module communication
        DDS::DomainParticipant* participant = nullptr;
        
        // Try to find participant in our local map first
        for (auto& pair : TopicManager::participants) {
            // Check if this participant matches the ID (this is a simplified approach)
            participant = pair.second;
            break; // Use the first available participant for now
        }
        
        if (!participant) {
            return -1; // Participant not found
        }
        
        // Check if topic already exists
        auto topic_it = TopicManager::topics.find(topic_name);
        if (topic_it != TopicManager::topics.end()) {
            return 0; // Topic already exists
        }
        
        // Register type support first
        DDS::ReturnCode_t register_result = DDS::BytesTypeSupport::get_instance()->register_type(
            participant,
            type_name.c_str()
        );
        
        if (register_result != DDS::RETCODE_OK) {
            return -1; // Failed to register type
        }
        
        // Create topic with properly initialized QoS
        DDS::TopicQos topic_qos;
        DDS_DefaultTopicQosInitial(&topic_qos);
        
        DDS::Topic* topic = participant->create_topic(
            topic_name.c_str(), 
            type_name.c_str(),
            topic_qos, 
            nullptr, 
            DDS::STATUS_MASK_NONE
        );
        
        if (topic) {
            TopicManager::topics[topic_name] = topic;
            return 1; // Topic created successfully
        } else {
            return -1; // Failed to create topic
        }
    }, py::arg("participant_id"), py::arg("topic_name"), py::arg("type_name") = "Bytes", 
       "Create Topic using participant ID (no pointer passing)");
    
    // Pure ID-based Topic creation - completely no pointer passing
    m.def("create_topic_pure_id", [](int participant_id, const std::string& topic_name, 
                                     const std::string& type_name = "Bytes") -> int {
        // Get participant from domain module using cross-module communication
        // This is a simplified approach - in a real implementation, we'd have proper module communication
        
        // For now, we'll use the existing participant registration mechanism
        // but return a topic ID instead of requiring pointer passing
        
        // Check if topic already exists
        auto topic_it = TopicManager::topics.find(topic_name);
        if (topic_it != TopicManager::topics.end()) {
            return 0; // Topic already exists
        }
        
        // Find participant in our local map (this should be registered by domain module)
        DDS::DomainParticipant* participant = nullptr;
        for (auto& pair : TopicManager::participants) {
            participant = pair.second;
            break; // Use the first available participant for now
        }
        
        if (!participant) {
            return -1; // Participant not found
        }
        
        // Register type support first
        DDS::ReturnCode_t register_result = DDS::BytesTypeSupport::get_instance()->register_type(
            participant,
            type_name.c_str()
        );
        
        if (register_result != DDS::RETCODE_OK) {
            return -1; // Failed to register type
        }
        
        // Create topic with properly initialized QoS
        DDS::TopicQos topic_qos;
        DDS_DefaultTopicQosInitial(&topic_qos);
        
        DDS::Topic* topic = participant->create_topic(
            topic_name.c_str(), 
            type_name.c_str(),
            topic_qos, 
            nullptr, 
            DDS::STATUS_MASK_NONE
        );
        
        if (topic) {
            TopicManager::topics[topic_name] = topic;
            // Return a topic ID (we'll use a simple hash of the topic name for now)
            int topic_id = std::hash<std::string>{}(topic_name) % 10000;
            return topic_id; // Return topic ID instead of success flag
        } else {
            return -1; // Failed to create topic
        }
    }, py::arg("participant_id"), py::arg("topic_name"), py::arg("type_name") = "Bytes", 
       "Create Topic using participant ID (pure ID-based, no pointer passing)");
    
    // Create ContentFilteredTopic
    m.def("create_content_filtered_topic", [](int domain_id, const std::string& topic_name,
                                             const std::string& filtered_topic_name,
                                             const std::string& filter_expression,
                                             const std::vector<std::string>& filter_parameters = {}) -> int {
        auto participant_it = TopicManager::participants.find(domain_id);
        if (participant_it == TopicManager::participants.end()) {
            return -1; // Participant not found
        }
        
        auto topic_it = TopicManager::topics.find(topic_name);
        if (topic_it == TopicManager::topics.end()) {
            return -1; // Source topic not found
        }
        
        DDS::DomainParticipant* participant = participant_it->second;
        DDS::Topic* source_topic = topic_it->second;
        
        // Create content filtered topic
        DDS::ContentFilteredTopic* filtered_topic = participant->create_contentfilteredtopic(
            filtered_topic_name.c_str(),
            source_topic,
            filter_expression.c_str(),
            DDS::StringSeq() // Convert vector to StringSeq if needed
        );
        
        if (filtered_topic) {
            TopicManager::content_filtered_topics[filtered_topic_name] = filtered_topic;
            return 1; // Created successfully
        } else {
            return -1; // Failed to create
        }
    }, py::arg("domain_id"), py::arg("topic_name"), py::arg("filtered_topic_name"), 
       py::arg("filter_expression"), py::arg("filter_parameters") = std::vector<std::string>(),
       "Create ContentFilteredTopic");
    
    // Create MultiTopic
    m.def("create_multi_topic", [](int domain_id, const std::string& multi_topic_name,
                                   const std::string& type_name,
                                   const std::string& subscription_expression,
                                   const std::vector<std::string>& expression_parameters = {}) -> int {
        auto participant_it = TopicManager::participants.find(domain_id);
        if (participant_it == TopicManager::participants.end()) {
            return -1; // Participant not found
        }
        
        DDS::DomainParticipant* participant = participant_it->second;
        
        // Create multi topic
        DDS::MultiTopic* multi_topic = participant->create_multitopic(
            multi_topic_name.c_str(),
            type_name.c_str(),
            subscription_expression.c_str(),
            nullptr  // expression_parameters - using nullptr for now
        );
        
        if (multi_topic) {
            TopicManager::multi_topics[multi_topic_name] = multi_topic;
            return 1; // Created successfully
        } else {
            return -1; // Failed to create
        }
    }, py::arg("domain_id"), py::arg("multi_topic_name"), py::arg("type_name"),
       py::arg("subscription_expression"), py::arg("expression_parameters") = std::vector<std::string>(),
       "Create MultiTopic");
    
    // Get Topic information
    m.def("get_topic_info", [](const std::string& topic_name) -> py::object {
        auto topic_it = TopicManager::topics.find(topic_name);
        if (topic_it == TopicManager::topics.end()) {
            return py::none();
        }
        
        DDS::Topic* topic = topic_it->second;
        py::dict info;
        info["name"] = topic_name;
        info["type_name"] = topic->get_type_name();
        info["participant"] = topic->get_participant() ? "valid" : "invalid";
        return info;
    }, py::arg("topic_name"), "Get Topic information");
    
    // Register participant for integration (ID-based only)
    m.def("register_participant_by_id", [](int domain_id, int participant_id) -> bool {
        // Topic模块不应该自己创建域参与者，应该从域模块获取
        // 这里只是记录映射关系，实际的域参与者由域模块管理
        TopicManager::participants[domain_id] = nullptr; // 占位符，实际指针由域模块提供
        return true;
    }, py::arg("domain_id"), py::arg("participant_id"), "Register DomainParticipant by ID for integration");
    
    // Check if participant exists (ID-based only, no pointer passing)
    m.def("participant_exists", [](int domain_id) -> bool {
        auto participant_it = TopicManager::participants.find(domain_id);
        return (participant_it != TopicManager::participants.end());
    }, py::arg("domain_id"), "Check if participant exists by domain ID");
    
    // Check if topic exists (ID-based only, no pointer passing)
    m.def("topic_exists", [](const std::string& topic_name) -> bool {
        auto topic_it = TopicManager::topics.find(topic_name);
        return (topic_it != TopicManager::topics.end());
    }, py::arg("topic_name"), "Check if topic exists by name");
    
    // Delete Topic
    m.def("delete_topic", [](const std::string& topic_name) -> bool {
        auto topic_it = TopicManager::topics.find(topic_name);
        if (topic_it == TopicManager::topics.end()) {
            return false; // Topic not found
        }
        
        // Topic deletion is handled by DomainParticipant
        TopicManager::topics.erase(topic_it);
        return true;
    }, py::arg("topic_name"), "Delete Topic (remove from management)");
    
    // Cleanup
    m.def("finalize", []() {
        TopicManager::cleanup();
        
        DDS::DomainParticipantFactory *factory = DDS::DomainParticipantFactory::get_instance();
        if (factory) {
            DDS::ReturnCode_t result = factory->finalize_instance();
            return true;
        }
        return true;
    }, "Cleanup ZRDDS Topic system");
    
    // Utility functions
    m.def("get_participant_count", []() {
        return static_cast<int>(TopicManager::participants.size());
    }, "Get number of domain participants");
    
    m.def("get_topic_count", []() {
        return static_cast<int>(TopicManager::topics.size());
    }, "Get number of topics");
    
    m.def("get_content_filtered_topic_count", []() {
        return static_cast<int>(TopicManager::content_filtered_topics.size());
    }, "Get number of content filtered topics");
    
    m.def("get_multi_topic_count", []() {
        return static_cast<int>(TopicManager::multi_topics.size());
    }, "Get number of multi topics");
    
    // API info
    m.def("get_api_info", []() {
        py::dict info;
        info["message"] = "ZRDDS Topic Module - Focused on Topic functionality";
        info["participant_count"] = TopicManager::participants.size();
        info["topic_count"] = TopicManager::topics.size();
        info["content_filtered_topic_count"] = TopicManager::content_filtered_topics.size();
        info["multi_topic_count"] = TopicManager::multi_topics.size();
        
        py::list functions;
        functions.append(py::str("get_participant_factory"));
        functions.append(py::str("init"));
        functions.append(py::str("create_domain_participant"));
        functions.append(py::str("create_topic"));
        functions.append(py::str("create_content_filtered_topic"));
        functions.append(py::str("create_multi_topic"));
        functions.append(py::str("get_topic_info"));
        functions.append(py::str("delete_topic"));
        functions.append(py::str("finalize"));
        info["main_functions"] = functions;
        return info;
    });
}
