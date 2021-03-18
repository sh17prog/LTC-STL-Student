#pragma once
#include <vector>
#include <string>
#include <stdexcept>

template<class Container, class Song_t>
class StaticPlaylist
{
public:
    /** @todo Member traits */
    using const_iterator  = typename Container::const_iterator;
    using size_type       = typename Container::size_type;
    using value_type      = typename Container::value_type;
    using reference       = typename Container::reference;
    using const_reference = typename Container::const_reference;
    using iterator        = typename Container::iterator;
    using difference_type = typename Container::difference_type;

    /** @todo Iterators */
    const_iterator begin() {
        return m_tracklist.cbegin();
    }

    const_iterator end() {
        return m_tracklist.cend();
    }

    StaticPlaylist() = default;

    /** @todo Constructor from any reversible sequence container */
    template <class OtherContainer>
    StaticPlaylist(OtherContainer&& container)
        : m_tracklist({container.rbegin(), container.rend()}) {
    }
    /** @todo Assignment from any reversible sequence container */
    /** @todo Add track from initializer */
    template<class... Args>
    const Song_t& play(Args&&... songData) {
        m_tracklist.emplace_back(std::forward<Args>(songData)...);
        return current();
    }

    /** @todo Add track */
    const Song_t& play(const Song_t& song) {
        m_tracklist.emplace_back(song);
        return current();
    }

    /** @todo Get first track in playlist stack */
    const Song_t& current() const {
        return m_tracklist.back();
    }

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext() {
        if (!hasTracks()) {
            throw std::out_of_range("Exception current track is unavailable");
        }
        m_tracklist.pop_back();
    }

    /** @todo Amount of tracks in playlist */
    size_type count() const {
        return m_tracklist.size();
    }

    /** @todo Checks if playlist has any playable tracks */
    bool hasTracks() const {
        return !m_tracklist.empty();
    }

private:
    Container m_tracklist;
};
