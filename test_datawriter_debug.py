#!/usr/bin/env python3
"""
Debug test for DataWriter creation issue
"""
import sys
sys.path.insert(0, 'zrpy')

def debug_test():
    try:
        import _zrdds_domain
        import _zrdds_topic
        import _zrdds_publish
        
        print("=== DataWriter Debug Test ===")
        
        # Initialize modules
        _zrdds_domain.init()
        _zrdds_topic.init()
        _zrdds_publish.init()
        
        # Create domain participant
        qos_id = _zrdds_domain.create_participant_qos()
        participant_id = _zrdds_domain.create_domain_participant(80, qos_id)
        participant_ptr = _zrdds_domain.get_participant_ptr(participant_id)
        
        # Register participant with topic and publish modules
        _zrdds_topic.register_participant(80, participant_ptr)
        _zrdds_publish.register_participant(80, participant_ptr)
        
        # Create topic
        topic_result = _zrdds_topic.create_topic(80, "TestTopic")
        topic_ptr = _zrdds_topic.get_topic_ptr("TestTopic")
        _zrdds_publish.register_topic("TestTopic", topic_ptr)
        
        # Create publisher
        publisher_id = _zrdds_publish.create_publisher(80)
        print(f"Publisher ID: {publisher_id}")
        
        # Check publisher count
        pub_count = _zrdds_publish.get_publisher_count()
        print(f"Publisher count: {pub_count}")
        
        # Create datawriter - this is where the problem occurs
        print("Creating DataWriter...")
        
        # Try to create DataWriter with explicit QoS
        qos_id = _zrdds_publish.create_datawriter_qos()
        print(f"Created DataWriter QoS with ID: {qos_id}")
        
        datawriter_id = _zrdds_publish.create_datawriter(publisher_id, "TestTopic", qos_id)
        print(f"DataWriter ID: {datawriter_id}")
        
        if datawriter_id == -1:
            print("DataWriter creation failed!")
            # Clean up and return
            if publisher_id != -1:
                _zrdds_publish.delete_publisher(publisher_id)
            _zrdds_topic.delete_topic("TestTopic")
            _zrdds_domain.delete_domain_participant(participant_id)
            _zrdds_domain.delete_participant_qos(qos_id)
            return
        
        # Check if datawriter was stored properly
        dw_count = _zrdds_publish.get_datawriter_count()
        print(f"DataWriter count: {dw_count}")
        
        # Get datawriter pointer
        datawriter_ptr = _zrdds_publish.get_datawriter_ptr(datawriter_id)
        print(f"DataWriter pointer: {type(datawriter_ptr)} - {datawriter_ptr}")
        
        if datawriter_ptr is None:
            print("DataWriter pointer is None - creation failed!")
        elif hasattr(datawriter_ptr, '__str__') and 'NULL' in str(datawriter_ptr):
            print("DataWriter pointer is NULL capsule - creation failed!")
        
        # Cleanup
        if datawriter_id != -1:
            _zrdds_publish.delete_datawriter(datawriter_id)
        if publisher_id != -1:
            _zrdds_publish.delete_publisher(publisher_id)
        _zrdds_topic.delete_topic("TestTopic")
        _zrdds_domain.delete_domain_participant(participant_id)
        _zrdds_domain.delete_participant_qos(qos_id)
        
        print("=== Debug Test Completed ===")

    except Exception as e:
        print(f"Error: {e}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    debug_test()
