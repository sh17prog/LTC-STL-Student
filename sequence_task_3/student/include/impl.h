#pragma once
#include <vector>
#include <string>
#include <stdexcept>

template<class Container, class Song_t>
class DynamicPlaylist
{
public:
    /** @todo Member traits */
    using size_type = typename Container::size_type;
    using self_type = DynamicPlaylist<Container, Song_t>;
    using const_iterator = typename Container::const_iterator;

    /** @todo Iterators */
    const_iterator begin() const {
        return m_tracklist.cbegin();
    }

    const_iterator end() const {
        return m_tracklist.cend();
    }

    DynamicPlaylist() = default;

    /** @todo Constructor from two iterators*/
    template <class Iter>
    DynamicPlaylist(Iter iterBegin, Iter iterEnd)
         : m_tracklist(iterBegin, iterEnd) {
    }
    /** @todo Set track as currently played from initializer */
    template<class... Args>
    const Song_t& play(Args&&... songData) {
        m_tracklist.emplace_front(std::forward<Args>(songData)...);
        return current();
    }

    /** @todo Set track as currently played from lvalue */
    const Song_t& play(const Song_t& song) {
        m_tracklist.push_front(song);
        return current();
    }

    /** @todo Set track to be played next from initializer */
    template<class... Args>
    void playNext(Args&&... songData) {
       if (!hasTracks()) {
            play(std::forward<Args>(songData)...);
        } else {
            m_tracklist.emplace(std::next(m_tracklist.begin()), std::forward<Args>(songData)...);
        }
    }

    /** @todo Set track to be played next from lvalue */
    void playNext(const Song_t& song) {
        if (!hasTracks()) {
            play(song);
        } else {
            m_tracklist.insert(std::next(m_tracklist.begin()), song);
        }
    }

    /** @todo Add track to the end of the queue from initializer */
    template<class... Args>
    void add(Args&&... songData) {
        m_tracklist.emplace_back(std::forward<Args>(songData)...);
    }

    /** @todo Add track to the end of the queue from lvalue */
    void add(const Song_t& song) {
        m_tracklist.push_back(song);
    }

    /** @todo Get first track in playlist queue */
    const Song_t& current() const {
        return m_tracklist.front();
    }

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext() {
        if (!hasTracks()) {
            throw  std::out_of_range("next track is unavailable");
        }
        m_tracklist.pop_front();
    }

    /** @todo Amount of tracks in playlist */
    size_type count() const {
        return m_tracklist.size();
    }

    /** @todo Checks if playlist has any playable tracks */
    bool hasTracks() const {
        return count() > 0;
    }

private:
    Container m_tracklist;
};
