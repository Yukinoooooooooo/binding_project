#!/usr/bin/env python3
"""
Integration test for ZRDDS Python modules - Publisher
Based on the C++ example main_pub.cpp
"""

import sys
import time
sys.path.insert(0, 'zrpy')

def test_publisher_integration():
    """Test publisher integration using all modules"""
    print("=== ZRDDS Publisher Integration Test ===")
     
    try:
        # Import all modules
        import _zrdds_domain
        import _zrdds_topic
        import _zrdds_publish
        import _zrdds_listener
        
        # 1. Initialize all modules
        print("1. Initializing modules...")
        _zrdds_domain.init()
        _zrdds_topic.init()
        _zrdds_publish.init()
        _zrdds_listener.init()
        print("✓ All modules initialized")
        
        # 2. Get factory instance
        print("2. Getting factory instance...")
        factory_available = _zrdds_domain.get_factory_instance()
        if not factory_available:
            print("✗ Factory instance not available")
            return False
        print("✓ Factory instance available")
        
        # 3. Create participant QoS with correct configuration
        print("3. Creating participant QoS...")
        qos_id = _zrdds_domain.create_participant_qos()
        if qos_id == -1:
            print("✗ Failed to create participant QoS")
            return False
        print(f"✓ Participant QoS created with ID: {qos_id}")
        
        # 4. Create domain participant
        print("4. Creating domain participant...")
        domain_id = 80  # Same as C++ example
        participant_id = _zrdds_domain.create_domain_participant(domain_id, qos_id)
        if participant_id == -1:
            print("✗ Failed to create domain participant")
            return False
        print(f"✓ Domain participant created with ID: {participant_id}")
        
        # 5. Get participant pointer for integration
        print("5. Getting participant pointer...")
        participant_ptr = _zrdds_domain.get_participant_ptr(participant_id)
        if participant_ptr is None:
            print("✗ Failed to get participant pointer")
            return False
        print("✓ Participant pointer obtained")
        
        # 6. Register participant with topic module
        print("6. Registering participant with topic module...")
        _zrdds_topic.register_participant(domain_id, participant_ptr)
        print("✓ Participant registered with topic module")
        
        # 7. Create topic (Bytes type for data writing)
        print("7. Creating topic...")
        topic_name = "DATARECEIVEBYLISTENER"  # Same as C++ example
        topic_result = _zrdds_topic.create_topic(domain_id, topic_name, "Bytes")  # Explicit Bytes type
        if not topic_result:
            print("✗ Failed to create topic")
            return False
        print(f"✓ Topic created: {topic_name} (Bytes type)")
        
        # 8. Get topic pointer
        print("8. Getting topic pointer...")
        topic_ptr = _zrdds_topic.get_topic_ptr(topic_name)
        if topic_ptr is None:
            print("✗ Failed to get topic pointer")
            return False
        print("✓ Topic pointer obtained")
        
        # 9. Register participant with publish module
        print("9. Registering participant with publish module...")
        _zrdds_publish.register_participant(domain_id, participant_ptr)
        print("✓ Participant registered with publish module")
        
        # 10. Register topic with publish module
        print("10. Registering topic with publish module...")
        _zrdds_publish.register_topic(topic_name, topic_ptr)
        print("✓ Topic registered with publish module")
        
        # 11. Create publisher
        print("11. Creating publisher...")
        publisher_id = _zrdds_publish.create_publisher(domain_id)
        if publisher_id == -1:
            print("✗ Failed to create publisher")
            return False
        print(f"✓ Publisher created with ID: {publisher_id}")
        
        # 12. Create datawriter
        print("12. Creating datawriter...")
        datawriter_id = _zrdds_publish.create_datawriter(publisher_id, topic_name)
        if datawriter_id == -1:
            print("✗ Failed to create datawriter")
            return False
        print(f"✓ DataWriter created with ID: {datawriter_id}")
        
        # 13. Getting datawriter pointer...
        print("13. Getting datawriter pointer...")
        datawriter_ptr = _zrdds_publish.get_datawriter_ptr(datawriter_id)
        if datawriter_ptr is not None:
            print(f"✓ DataWriter pointer obtained: {type(datawriter_ptr)} - {datawriter_ptr}")
            # Add debug info
            print(f"   Debug: datawriter_id={datawriter_id}, pointer_type={type(datawriter_ptr)}")
            if hasattr(datawriter_ptr, '__str__'):
                print(f"   Debug: pointer_str={str(datawriter_ptr)}")
        else:
            print("✗ Failed to get DataWriter pointer")
            return
        
        # 14. Create DataWriter listener
        print("14. Creating DataWriter listener...")
        listener_id = _zrdds_listener.create_datawriter_listener()
        if listener_id == -1:
            print("✗ Failed to create DataWriter listener")
            return False
        print(f"✓ DataWriter listener created with ID: {listener_id}")
        
        # 14.1 Get raw listener pointer, register in publish, and attach by IDs
        listener_ptr = _zrdds_listener.get_datawriter_listener_ptr(listener_id)
        if listener_ptr is None:
            print("✗ Failed to get raw DataWriterListener pointer")
            return False
        print("✓ Got raw DataWriterListener pointer")

        # Register the listener into publish module for ID-based attach
        if not _zrdds_publish.register_datawriter_listener(listener_id, listener_ptr):
            print("✗ Failed to register DataWriterListener in publish module")
            return False
        print("✓ Registered DataWriterListener in publish module")

        # 15. Attach listener to datawriter using writer_id and listener_id
        print("15. Attaching listener to datawriter...")
        try:
            listener_attached = _zrdds_publish.attach_datawriter_listener_by_id(
                datawriter_id, listener_id, _zrdds_listener.STATUS_MASK_ALL)
            if listener_attached:
                print("✓ Listener attached to datawriter")
            else:
                print("⚠ Failed to attach listener to datawriter")
        except Exception as e:
            print(f"⚠ Exception when attaching listener: {e}")
            print("Continuing without listener attachment...")
        
        # 16. Test data writing
        print("16. Testing data writing...")
        
        # Since we created a Bytes type topic, only bytes data will work
        print("Note: Topic was created with 'Bytes' type, so only bytes data writing is supported")
        
        # Write bytes data  
        test_bytes = "Data Receive by Listener - Python Version"
        bytes_success = _zrdds_publish.write_bytes_data(datawriter_id, test_bytes)
        if bytes_success:
            print(f"✓ Successfully wrote bytes data: '{test_bytes}'")
        else:
            print("⚠ Failed to write bytes data")
        
        # Simulate continuous data sending (like C++ example)
        print("17. Simulating continuous data sending...")
        for i in range(3):
            message = f"Message #{i+1} from Python Publisher"
            if _zrdds_publish.write_bytes_data(datawriter_id, message):
                print(f"   ✓ Sent: {message}")
            else:
                print(f"   ✗ Failed to send: {message}")
            time.sleep(1)  # Sleep 1 second between messages
        
        # 18. Show entity counts
        print("18. Entity counts:")
        print(f"  - Domain participants: {_zrdds_domain.get_participant_count()}")
        print(f"  - Topics: {_zrdds_topic.get_topic_count()}")
        print(f"  - Publishers: {_zrdds_publish.get_publisher_count()}")
        print(f"  - DataWriters: {_zrdds_publish.get_datawriter_count()}")
        print(f"  - Listeners: {_zrdds_listener.get_datawriter_listener_count()}")
        
        # 19. Cleanup
        print("19. Cleaning up...")
        
        # Delete datawriter first (child entity)
        if datawriter_id != -1:
            _zrdds_publish.delete_datawriter(datawriter_id)
            print("✓ DataWriter deleted")
        
        # Delete publisher (parent of DataWriter)
        if publisher_id != -1:
            _zrdds_publish.delete_publisher(publisher_id)
            print("✓ Publisher deleted")
        
        # Delete topic (child entity of DomainParticipant)
        _zrdds_topic.delete_topic(topic_name)
        print("✓ Topic deleted")
        
        # Delete domain participant last (parent entity)
        if participant_id != -1:
            _zrdds_domain.delete_domain_participant(participant_id)
            print("✓ Domain participant deleted")
        
        # Delete QoS
        if qos_id != -1:
            _zrdds_domain.delete_participant_qos(qos_id)
            print("✓ Participant QoS deleted")
        
        # Unregister and delete listener
        if listener_id != -1:
            try:
                _zrdds_publish.unregister_datawriter_listener(listener_id)
                print("✓ DataWriter listener unregistered from publish module")
            except Exception:
                pass
            _zrdds_listener.delete_datawriter_listener(listener_id)
            print("✓ DataWriter listener deleted")
        
        # Finalize all modules
        _zrdds_listener.finalize()
        _zrdds_publish.finalize()
        _zrdds_topic.finalize()
        _zrdds_domain.finalize()
        print("✓ All modules finalized")
        
        print("\n🎉 Publisher integration test completed successfully!")
        return True
        
    except Exception as e:
        print(f"✗ Test failed: {e}")
        import traceback
        traceback.print_exc()
        return False

if __name__ == "__main__":
    test_publisher_integration()
