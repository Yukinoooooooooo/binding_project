#!/usr/bin/env python3
"""
ZRDDS Communication Test - Publisher and Subscriber
Tests real data transmission between publisher and subscriber across DDS domain
"""

import sys
import time
import threading
sys.path.insert(0, 'zrpy')

def run_publisher():
    """Run publisher in separate thread"""
    print("🚀 Publisher thread started")
    
    try:
        import _zrdds_domain, _zrdds_topic, _zrdds_publish
        
        # Initialize modules
        _zrdds_domain.init()
        _zrdds_topic.init()
        _zrdds_publish.init()
        
        # Create publisher workflow
        _zrdds_domain.get_factory_instance()
        qos_id = _zrdds_domain.create_participant_qos()
        participant_id = _zrdds_domain.create_domain_participant(80, qos_id)
        participant_ptr = _zrdds_domain.get_participant_ptr(participant_id)
        
        _zrdds_topic.register_participant(80, participant_ptr)
        _zrdds_topic.create_topic(80, "COMM_TEST", "Bytes")
        topic_ptr = _zrdds_topic.get_topic_ptr("COMM_TEST")
        
        _zrdds_publish.register_participant(80, participant_ptr)
        _zrdds_publish.register_topic("COMM_TEST", topic_ptr)
        publisher_id = _zrdds_publish.create_publisher(80)
        datawriter_id = _zrdds_publish.create_datawriter(publisher_id, "COMM_TEST")
        
        print("📡 Publisher ready, waiting for subscriber...")
        time.sleep(2)  # Wait for subscriber to be ready
        
        # Send data
        print("📤 Starting data transmission...")
        for i in range(5):
            message = f"Publisher Message #{i+1} at {time.strftime('%H:%M:%S')}"
            if _zrdds_publish.write_bytes_data(datawriter_id, message):
                print(f"   ✅ Sent: {message}")
            else:
                print(f"   ❌ Failed to send: {message}")
            time.sleep(2)
        
        print("📤 Publisher finished sending data")
        
        # Cleanup
        _zrdds_publish.delete_datawriter(datawriter_id)
        _zrdds_publish.delete_publisher(publisher_id)
        _zrdds_topic.delete_topic("COMM_TEST")
        _zrdds_domain.delete_domain_participant(participant_id)
        _zrdds_domain.delete_participant_qos(qos_id)
        
        _zrdds_publish.finalize()
        _zrdds_topic.finalize()
        _zrdds_domain.finalize()
        
        print("🧹 Publisher cleaned up")
        
    except Exception as e:
        print(f"❌ Publisher error: {e}")
        import traceback
        traceback.print_exc()

def run_subscriber():
    """Run subscriber in separate thread"""
    print("📡 Subscriber thread started")
    
    try:
        import _zrdds_domain, _zrdds_topic, _zrdds_subscribe
        
        # Initialize modules
        _zrdds_domain.init()
        _zrdds_topic.init()
        _zrdds_subscribe.init()
        
        # Create subscriber workflow
        _zrdds_domain.get_factory_instance()
        qos_id = _zrdds_domain.create_participant_qos()
        participant_id = _zrdds_domain.create_domain_participant(80, qos_id)
        participant_ptr = _zrdds_domain.get_participant_ptr(participant_id)
        
        _zrdds_topic.register_participant(80, participant_ptr)
        _zrdds_topic.create_topic(80, "COMM_TEST", "Bytes")
        topic_ptr = _zrdds_topic.get_topic_ptr("COMM_TEST")
        
        _zrdds_subscribe.register_participant(80, participant_ptr)
        _zrdds_subscribe.register_topic("COMM_TEST", topic_ptr)
        subscriber_id = _zrdds_subscribe.create_subscriber(80)
        datareader_id = _zrdds_subscribe.create_datareader(subscriber_id, "COMM_TEST")
        
        print("📡 Subscriber ready, waiting for data...")
        
        # Receive data
        received_count = 0
        start_time = time.time()
        
        while received_count < 5 and (time.time() - start_time) < 20:  # Wait up to 20 seconds
            # Try to read data
            data = _zrdds_subscribe.read_bytes_data(datareader_id)
            if data is not None:
                received_count += 1
                print(f"   📥 Received: {data}")
            else:
                time.sleep(0.5)  # Wait a bit before trying again
        
        if received_count == 5:
            print(f"✅ Subscriber received all {received_count} messages successfully!")
        else:
            print(f"⚠️  Subscriber received {received_count}/5 messages")
        
        # Cleanup
        _zrdds_subscribe.delete_datareader(datareader_id)
        _zrdds_subscribe.delete_subscriber(subscriber_id)
        _zrdds_topic.delete_topic("COMM_TEST")
        _zrdds_domain.delete_domain_participant(participant_id)
        _zrdds_domain.delete_participant_qos(qos_id)
        
        _zrdds_subscribe.finalize()
        _zrdds_topic.finalize()
        _zrdds_domain.finalize()
        
        print("🧹 Subscriber cleaned up")
        
    except Exception as e:
        print(f"❌ Subscriber error: {e}")
        import traceback
        traceback.print_exc()

def main():
    """Main communication test"""
    print("=== ZRDDS Communication Test ===")
    print("Testing real data transmission between publisher and subscriber")
    print("Domain ID: 80, Topic: COMM_TEST, Type: Bytes")
    print()
    
    # Start subscriber thread first
    sub_thread = threading.Thread(target=run_subscriber)
    sub_thread.daemon = True
    sub_thread.start()
    
    # Wait a bit for subscriber to be ready
    time.sleep(1)
    
    # Start publisher thread
    pub_thread = threading.Thread(target=run_publisher)
    pub_thread.daemon = True
    pub_thread.start()
    
    # Wait for both threads to complete
    pub_thread.join()
    sub_thread.join()
    
    print("\n🎉 Communication test completed!")
    print("If you saw data being transmitted and received, DDS communication is working!")

if __name__ == "__main__":
    main()
